//
//  Pool.cpp
//  
//
//  Created by Sourgroup on 12/13/17.
//
/*    int MyID;
 block Delta;
 AES_KEY Private_AES_KEY, Public_AES_KEY;
 uint64_t Public_Count=0, Private_Count=0;
 Network *IO;
 MOTSet *MOT;
 block *LabelBuffer;
 uint32_t LabelBufferIndex;
 block *BitBuffer;
 uint32_t BitBufferIndex;
 block *TupleBuffer;
 uint32_t TupleBufferIndex;
 block *Pool;
 block *PoolBuffer;
 uint32_t PoolSize;
 unsigned char BucketSize;
 uint32_t *index;
 uint32_t BufferSize;
 */

#include "Pool.hpp"
MPool MP;
void MPool::Setup(int id,uint32_t PS,unsigned char BS,uint32_t Buffer,MOTSet *MMOT)
{
    AdvSetup(id,PS,BS,Buffer,Buffer,Buffer,Buffer,MMOT);
}
void MPool::AdvSetup(int id,uint32_t PS,unsigned char BS,uint32_t LBS,uint32_t BBS,uint32_t TBS,uint32_t Buffer,MOTSet *MMOT)
{
    MyID=id;
    PoolSize=PS;
    BucketSize=BS;
    BufferSize=Buffer;
  
    //LabelBufferSize=Buffer;
   // BitBufferSize=Buffer;
   // TupleBufferSize=Buffer;
    LabelBufferSize=LBS;
    BitBufferSize=BBS;
    TupleBufferSize=TBS;
    /*
    BitBufferSize=BBS;
    TupleBufferSize=TBS;
*/
    PoolBufferSize=TupleBufferSize*BucketSize;

    IO=MMOT->IO;
    MOT=MMOT;
    block tmp[2];
    Delta=MMOT->Delta;
    delta=_mm_and_si128(Delta,bed1);
    tmp[0]=_mm_set_epi32(0,0,0,1);
    tmp[1]=_mm_set_epi32(id,0,0,id);
    AES_set_encrypt_key(tmp[0],&Public_AES_KEY);
    AES_set_encrypt_key(tmp[1],&Private_AES_KEY);
    LabelBuffer=(block*)_mm_malloc(sizeof(block)*(LabelBufferSize/*LabelBuffer*/+BitBufferSize*(PartyNumber-1)*2/*BitBuffer*/+TupleBufferSize*(PartyNumber-1)*2*3/*TupleBuffer*/+PoolSize*(PartyNumber-1)*2*3/*Pool*/+TupleBufferSize*BucketSize*(PartyNumber-1)*2*3/*PoolBuffer*/),16);
    BitBuffer=LabelBuffer+LabelBufferSize;
    TupleBuffer=BitBuffer+BitBufferSize*(PartyNumber-1)*2;
    Pool=TupleBuffer+TupleBufferSize*(PartyNumber-1)*2*3;
    PoolBuffer=Pool+PoolSize*(PartyNumber-1)*2*3;
    InputWire[0]=(wire**)_mm_malloc(sizeof(wire*)*BufferSize*PartyNumber,16);
    for(int i=1;i<PartyNumber;i++)
        InputWire[i]=&(InputWire[i-1][BufferSize]);
    //    unsigned char **InputMaskedValue[PartyNumber];
    InputMaskedValue[0]=(unsigned char*)malloc(sizeof(unsigned char)*BufferSize*PartyNumber);
    for(int i=1;i<PartyNumber;i++)
        InputMaskedValue[i]=&(InputMaskedValue[i-1][BufferSize]);
    InputMacBuffer=(block*)_mm_malloc(sizeof(block)*PartyNumber*BufferSize*2,16);
    memset(InputMacBuffer,0,16*PartyNumber*BufferSize*2);
    if(MyID==0)
    {
        InputLabelBuffer=(block*)_mm_malloc(sizeof(block)*PartyNumber*(PartyNumber-1)*BufferSize*2,16);
    }
    else{
        InputLabelBuffer=(block*)_mm_malloc(sizeof(block)*PartyNumber*BufferSize*2,16);
    }
    permutation=(uint32_t*)_mm_malloc(sizeof(uint32_t)*TupleBufferSize*BS,16);
    visited=(bool*)malloc(sizeof(bool)*PS);
    for(int i=0;i<PS;i++)
        visited[i]=false;
    BitBufferIndex=Buffer;
    TupleBufferIndex=Buffer;
    RefreshLabel(LabelBuffer,LabelBufferSize);
    NewLeakyTuples(Pool,PoolSize+TupleBufferSize*BucketSize);
    for(int i=0;i<PartyNumber;i++)
    {
        InputExCount[2*i]=0;
        InputExCount[2*i+1]=0;
        InputCount[i]=0;
    }
}
void MPool::Close()
{
    _mm_free(LabelBuffer);
    _mm_free(permutation);
    _mm_free(InputWire[0]);
    _mm_free(InputMacBuffer);
    _mm_free(InputLabelBuffer);
    free(visited);
    free(InputMaskedValue[0]);
}
void MPool::NewLabels(block *dst, int n)
{
    
    if (n>LabelBufferSize)
    {
        RefreshLabel(dst,n);
        return;
    }
    if(LabelBufferIndex+n<=LabelBufferSize)
    {
        memcpy(dst,&(LabelBuffer[LabelBufferIndex]),16*n);
        LabelBufferIndex+=n;
    }
    else{
        int i=LabelBufferSize-LabelBufferIndex;
        memcpy(dst,&(LabelBuffer[LabelBufferIndex]),16*i);
        RefreshLabel(LabelBuffer,LabelBufferSize);
        memcpy(&(dst[i]),LabelBuffer,16*(n-i));
        LabelBufferIndex=n-i;
    }
}
void MPool::RefreshLabel(block *dst, int n)
{
    PRG(dst,n,&Private_AES_KEY,&Private_Count);
    for(int i=0;i<n;i++)
        dst[i]=_mm_and_si128(dst[i],bed1);
}
void MPool::Flip(wire *src)
{
    if(MyID==0)
    {
        for(int i=0;i<PartyNumber-1;i++)
        {
            src->Label[i]=_mm_xor_si128(src->Label[i],plainbit1);
        }
    }
    else
    {
        src->Label[0]=_mm_xor_si128(src->Label[0],delta);
    }
}

