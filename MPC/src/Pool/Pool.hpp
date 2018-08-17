//
//  Pool.hpp
//  
//
//  Created by Sourgroup on 12/13/17.
//

#ifndef Pool_hpp
#define Pool_hpp

#include <stdio.h>
#include "PRG.hpp"
#include "Wiremap.hpp"
#include "MOTE.hpp"
#include <openssl/sha.h>
class MPool{
private:
    int MyID;
    AES_KEY Private_AES_KEY, Public_AES_KEY;
    uint64_t Public_Count=0, Private_Count=0;
    MOTSet *MOT;
    block *LabelBuffer;
    uint32_t LabelBufferSize;
    uint32_t LabelBufferIndex;
    block *BitBuffer;
    uint32_t BitBufferSize;
    uint32_t BitBufferIndex;
    block *TupleBuffer;
    uint32_t TupleBufferSize;
    uint32_t TupleBufferIndex;
    block *Pool;
    block *PoolBuffer;
    uint32_t PoolBufferSize;
    uint32_t PoolBufferIndex;
    uint32_t PoolSize;
    unsigned char BucketSize;
    uint32_t *permutation;
    uint32_t permutationindex;
    uint32_t BufferSize;
    bool *visited;
    block *InputMacBuffer,*InputLabelBuffer;
    wire **InputWire[PartyNumber];
    unsigned char *InputMaskedValue[PartyNumber];
    int InputCount[PartyNumber];
    int InputExCount[PartyNumber*2];
    void RefreshLabel(block *dst, int n);
    void RefreshBits(block *dst, int n);
    void HaAnd(unsigned char *dst, block *src, int n,block *hashbed);
    void NewLeakyTuples(block *dst,int n);
    void CheckTuples(block *src,int n,block *hashbed);
    void CombineTuples();
    void RefreshBuffer();
public:
    void HaAndTest();
    block Delta;
    block delta;
    const block zeroblock=_mm_set_epi32(0,0,0,0);
    const block plainbit1=_mm_set_epi32(0,0,0,1);
    const block bed1=_mm_set_epi32(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFE);
    const block all1=_mm_set_epi32(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
    Network *IO;
    void Setup(int id,uint32_t PoolSize,unsigned char BucketSize,uint32_t BufferSize,MOTSet *MMOT);
    void AdvSetup(int id,uint32_t PS,unsigned char BS,uint32_t LBS,uint32_t BBS,uint32_t TBS,uint32_t Buffer,MOTSet *MMOT);
    void Close();
    void NewLabels(block *dst,int n);
    void NewBits(block *dst,int n);
    void NewTuples(block *dst,int n);
    bool CheckBit(block a,block b);
    void BatchInput(wire *dst, int id,unsigned char c);
    void BatchInputFlush();
  //  void CheckLabel(wire *src);
    unsigned char Reveal(wire *src);
    void Flip(wire *src);
};
extern MPool MP;
inline void AuthBitXor(block *dst, block *a, block *b)
{
    for(int i=0;i<2*(PartyNumber-1);i++)
    dst[i]=_mm_xor_si128(a[i],b[i]);
}
inline void hash(block *dst,block l, block r,int id, AES_KEY *key)
{
    block tmp[2*PartyNumber],mask;
    tmp[0]=_mm_xor_si128(l,_mm_slli_si128(r,1));
    for(int i=1;i<PartyNumber;i++)
    {
        mask=_mm_set_epi32(0,0,id,i);
        tmp[i]=_mm_xor_si128(tmp[0],mask);
    }
    mask=_mm_set_epi32(0,0,id,0);
    tmp[0]=_mm_xor_si128(tmp[0],mask);
    memcpy(&(tmp[PartyNumber]),tmp,PartyNumber*16);
    AES_ecb_encrypt_blks(tmp,PartyNumber,key);
    for(int i=0;i<PartyNumber;i++)
    {
        dst[i]=_mm_xor_si128(tmp[i],tmp[i+PartyNumber]);
    }
}
#endif /* Pool_hpp */
