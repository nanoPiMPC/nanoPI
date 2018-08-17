//
//  Bits.cpp
//  
//
//  Created by Sourgroup on 12/22/17.
//

#include "Bits.hpp"
void MPool::BatchInput(wire *dst, int id,unsigned char c)
{
    NewBits(dst->AuthBit,1);
    InputWire[id][InputCount[id]]=dst;
    if(id==MyID)
    {
        for(int i=0;i<PartyNumber;i++)
        {
            if(i!=MyID)
                InputExCount[2*i+1]+=16;
        }
        InputMaskedValue[id][InputCount[id]]=c^extract_bit(dst->AuthBit[0]);
        InputMacBuffer[BufferSize*id+InputCount[id]]=dst->AuthBit[1];
        for(int i=1;i<PartyNumber-1;i++)
            InputMacBuffer[BufferSize*MyID+InputCount[id]]=_mm_xor_si128(InputMacBuffer[BufferSize*MyID+InputCount[id]],dst->AuthBit[1+2*i]);
    }
    else{
        InputExCount[2*id]+=16;
        InputMacBuffer[BufferSize*id+InputCount[id]]=dst->AuthBit[id*2];
    }
    if(MyID!=0)
    {
        NewLabels(dst->Label,1);
        InputLabelBuffer[BufferSize*id+InputCount[id]]=dst->Label[0];
    }
    InputCount[id]++;
    if(InputCount[id]>=BufferSize)BatchInputFlush();
}
void MPool::BatchInputFlush()
{
    void* exsrc[PartyNumber];
    void* exdst[PartyNumber];
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(InputMacBuffer[BufferSize*i]);
        exdst[i]=&(InputMacBuffer[BufferSize*i+BufferSize*PartyNumber]);
    }
    AdvExchange(IO,exdst,exsrc,InputExCount);
    for(int i=0;i<InputCount[MyID];i++)
    {
        InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i]=zeroblock;
        for(int j=0;j<MyID;j++)
        {
            InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i]=_mm_xor_si128(InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i],InputMacBuffer[BufferSize*PartyNumber+BufferSize*j+i]);
        }
        for(int j=MyID+1;j<PartyNumber;j++)
        {
            InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i]=_mm_xor_si128(InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i],InputMacBuffer[BufferSize*PartyNumber+BufferSize*j+i]);
        }
    InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i]=_mm_xor_si128(InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i],InputMacBuffer[BufferSize*MyID+i]);
    if(_mm_testz_si128(InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i],all1)!=1)
        {
            InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i]=_mm_xor_si128(InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i],Delta);
            if(_mm_testz_si128(InputMacBuffer[BufferSize*PartyNumber+BufferSize*MyID+i],all1)==1)
            {
                InputMaskedValue[MyID][i]^=1;
            }
            else{
                printf("Input Error!\n");
                exit(0);
            }
        }
    }
    int tmpint;
    for(int i=0;i<PartyNumber;i++)
    {
        tmpint=InputExCount[2*i]>>4;
        InputExCount[2*i]=InputExCount[2*i+1]>>4;
        InputExCount[2*i+1]=tmpint;
    }
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=InputMaskedValue[MyID];
        exdst[i]=InputMaskedValue[i];
    }
    AdvExchange(IO,exdst,exsrc,InputExCount);
    if(MyID==0)
    {
        int Total=InputCount[0];
        for(int i=1;i<PartyNumber;i++)
        {
            Total+=InputCount[i];
            exdst[i]=&(InputLabelBuffer[(i-1)*BufferSize*PartyNumber]);
        }
        Gather(IO,0,exdst,Total*16);
        Total=0;
        for(int i=0;i<PartyNumber;i++)
        {
            for(int j=0;j<InputCount[i];j++)
            {
                for(int k=0;k<PartyNumber-1;k++)
                {
                    InputWire[i][j]->Label[k]=InputLabelBuffer[k*BufferSize*PartyNumber+Total];
                }
                Total++;
            }
        }
    }
    else
    {
        for(int i=0;i<PartyNumber;i++)
        {
            for(int j=0;j<InputCount[i];j++)
            {
                if(InputMaskedValue[i][j]==1)
                    InputLabelBuffer[BufferSize*i+j]=_mm_xor_si128(InputLabelBuffer[BufferSize*i+j],Delta);
            }
        }
        int Total=0;
        for(int i=0;i<PartyNumber;i++)
        {
            for(int j=0;j<InputCount[i];j++)
            {
                InputLabelBuffer[Total]=InputLabelBuffer[BufferSize*i+j];
                Total++;
            }
        }
        Gather(IO,0,InputLabelBuffer,16*Total);
    }
    for(int i=0;i<PartyNumber;i++)
    {
        InputCount[i]=0;
    }
     
}
unsigned char MPool::Reveal(wire *src)
{
    
    block tmp[PartyNumber];
    block auth[2];
    if(MyID==0)
    {
        tmp[0]=src->AuthBit[0];
        void *gatherdst[PartyNumber];
        for(int i=1;i<PartyNumber;i++)
            gatherdst[i]=&(tmp[i]);
        Gather(IO,0,gatherdst,16);
        for(int i=1;i<PartyNumber;i++)
        {
            if(!CheckBit(tmp[i],src->AuthBit[2*i-1]))
            {
                printf("Output Auth Error %d\n",i);
                exit(0);
            }
        }
        tmp[0]=_mm_xor_si128(tmp[0],src->Label[0]);
        for(int i=1;i<PartyNumber;i++)
        {
            tmp[0]=_mm_xor_si128(tmp[0],tmp[i]);
        }
        return extract_bit(tmp[0]);
    }
    else{
        Gather(IO,0,&(src->AuthBit[0]),16);
        return 2;
    }
}
/*
void MPool::CheckLabel(wire *src)
{
    if(MyID==0)
    {
        unsigned char bit[PartyNumber-1];
        block tmp1[2],tmp[2];
        for(int i=1;i<PartyNumber;i++)
        {
            IO->preceive(i,tmp,32);
            tmp1[0]=_mm_xor_si128(tmp[0],src->Label[i-1]);
            tmp1[1]=_mm_xor_si128(tmp[1],src->Label[i-1]);
            if(_mm_testz_si128(tmp1[0],all1)==1)
                bit[i-1]=0;
            else{
                if(_mm_testz_si128(tmp1[1],all1)==1)
                    bit[i-1]=1;
                else{
                    print(src->Label[i-1]);
                    print(tmp[0]);
                    print(tmp[1]);
                    
                    printf("Label Error %d\n",i);
                    return;
                }
            }
        }
        for(int i=1;i<PartyNumber;i++)
            printf("%d ",bit[i-1]);
        printf("\n");
    }
    else
    {
        block tmp[2];
        tmp[0]=src->Label[0];
        tmp[1]=_mm_xor_si128(tmp[0],Delta);
        IO->psend(0,tmp,32);
    }
}
*/
void MPool::NewBits(block *dst, int n)
{
    if (n>BitBufferSize)
    {
        RefreshBits(dst,n);
        return;
    }
    
    if(BitBufferIndex+n<=BitBufferSize)
    {
        memcpy(dst,&(BitBuffer[BitBufferIndex*2*(PartyNumber-1)]),16*2*n*(PartyNumber-1));
        BitBufferIndex+=n;
    }
    else{
        int i=BitBufferSize-BitBufferIndex;
        memcpy(dst,&(BitBuffer[BitBufferIndex*2*(PartyNumber-1)]),16*2*i*(PartyNumber-1));
        RefreshBits(BitBuffer,BitBufferSize);
        memcpy(&(dst[i*2*(PartyNumber-1)]),BitBuffer,16*2*(n-i)*(PartyNumber-1));
        BitBufferIndex=n-i;
    }
}
void MPool::RefreshBits(block *dst, int n)//Give n pairs of new AuthBits
{
    //  MOT->MultiOT(dst,n);
    if(n<=MOT->MOTBufferSize)
        MOT->MultiOT(dst,n);
    else{
        MOT->MultiOT(dst,MOT->MOTBufferSize);
        RefreshBits(dst+2*(PartyNumber-1)*MOT->MOTBufferSize,n-MOT->MOTBufferSize);
    }

}
bool MPool::CheckBit(block a,block b)
{
    block tmp=_mm_xor_si128(a,b);
    if((_mm_testz_si128(tmp,all1)==1)||(_mm_testz_si128(_mm_xor_si128(tmp,Delta),all1)==1)) return true;
    return false;
}
