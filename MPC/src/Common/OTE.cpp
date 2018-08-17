//
//  OTE.cpp
//
//
//  Created by Sourgroup on 12/13/17.
//
#include "OTE.hpp"
OTSet OTS;
unsigned long long OTCount=0;
double OTTime=0;
int OTNum=0;
void OTSet::Setup(int myid,int partnerid,block D,int buffersize,block seed,Network *N)
{
    size=buffersize/128+2;
    IO=N;
    MyID=myid;
    PartnerID=partnerid;
    OTBufferSize=buffersize;
    LabelBufferSize=buffersize;
    OTEtemp=(block *)_mm_malloc(sizeof(block)*(168*size*4+OTBufferSize/128+2+OTBufferSize*2+size*80+LabelBufferSize),16);
    OTEChoice=OTEtemp+168*size*4;
    OTBuffer=OTEChoice+OTBufferSize/128+2;
    index=OTBuffer+OTBufferSize*2;
    LabelBuffer=index+size*80;
    ChiThis=(block*)_mm_malloc(sizeof(block)*(OTBufferSize+256)*3,16);
    ChiThat=ChiThis+(OTBufferSize+256);
    Delta=D;
    unsigned char *p[2];
    p[0]=(unsigned char *)&D;
    p[1]=p[0]+7;
    p[0]=p[1]+8;
    for(int i=0;i<64;i++)
    {
        if(*p[0]>>7==1)MatrixDelta[i]=_mm_set_epi32(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
        else MatrixDelta[i]=_mm_set_epi32(0,0,0,0);
        if(*p[1]>>7==1)MatrixDelta[i+64]=_mm_set_epi32(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
        else MatrixDelta[i+64]=_mm_set_epi32(0,0,0,0);
        D=_mm_slli_epi64(D,1);
    }
    RandomSeed=_mm_set_epi32(3,2,3,4+MyID+PartnerID);
    AES_set_encrypt_key(RandomSeed,&Public_AES_KEY);
    RandomSeed=seed;
    AES_set_encrypt_key(RandomSeed,&Private_AES_KEY);
    Public_Count=0;
    Private_Count=0;
    RefreshLabel(LabelBuffer,LabelBufferSize);
    
    MatrixISetup();
    GarbleMatrix();
    ExtractChoiceZero();
    ExtractBaseOT();
    
    for(int i=0;i<168;i++)
    {
        BaseOTChoice[i]=(_mm_extract_epi8(ChoiceZero[i],0)>0);
        if(MyID<PartnerID)
        {
            BaseOTSend[i][0]=_mm_set_epi32(1,0,0,i);
            BaseOTSend[i][1]=_mm_set_epi32(1,1,0,i);
            if(BaseOTChoice[i]==0)
                BaseOTRec[i]=_mm_set_epi32(2,0,0,i);
            else
                BaseOTRec[i]=_mm_set_epi32(2,1,0,i);
        }
        else
        {
            BaseOTSend[i][0]=_mm_set_epi32(2,0,0,i);
            BaseOTSend[i][1]=_mm_set_epi32(2,1,0,i);
            if(BaseOTChoice[i]==0)
                BaseOTRec[i]=_mm_set_epi32(1,0,0,i);
            else
                BaseOTRec[i]=_mm_set_epi32(1,1,0,i);
        }
    }
    memcpy(MatrixI,MatrixINext,16*168);
    CCheckIndex[0]=_mm_set_epi32(0x80000000,0,0,0);
    for(int i=1;i<40;i++)
        CCheckIndex[i]=_mm_srli_epi64(CCheckIndex[i-1],1);
    CCheckIndex[40]=_mm_set_epi8(0,0,0,0,0,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff);
    memset(DeltaCheck,0,80*16);
    OTBufferIndex=buffersize;
}
void OTSet::OTClose()
{
    _mm_free(OTEtemp);
}
void OTSet::NewLabels(block *dst, int n)
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

void OTSet::RefreshLabel(block *dst, int n)
{
    PRG(dst,n,&Private_AES_KEY,&Private_Count);
}

void OTSet::MatrixISetup()
{
    MatrixINext[0]=_mm_set_epi32(0x80000000,0,0,0);
    for(int i=1;i<64;i++)
        MatrixINext[i]=_mm_srli_epi64(MatrixINext[i-1],1);
    MatrixINext[64]=_mm_set_epi32(0,0,0x80000000,0);
    for(int i=65;i<128;i++)
        MatrixINext[i]=_mm_srli_epi64(MatrixINext[i-1],1);
    memset(MatrixINext+128,0,40*16);
    for(int i=0;i<128;i++)
        ChoiceZero[i]=MatrixDelta[i];
    block tmp;
    NewLabels(&tmp,1);
    unsigned char *sign=(unsigned char*)&tmp;
    sign=sign+15;
    for(int i=128;i<168;i++)
    {
        if(*sign>>7==1) ChoiceZero[i]=_mm_set_epi32(0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF,0xFFFFFFFF);
        else ChoiceZero[i]=_mm_set_epi32(0,0,0,0);
        tmp=_mm_slli_epi64(tmp,1);
    }
}
void OTSet::GarbleMatrix()
{
    block indicator[168];
    NewLabels(indicator,168);
    unsigned char *pointer[168];
    for(int i=0;i<168;i+=2)
    {
        pointer[i]=(unsigned char *)&(indicator[i/2])+7;
        pointer[i+1]=(unsigned char *)&(indicator[i/2])+15;
    }
    for(int i=0;i<=63;i++)
    {
        for(int j=0;j<168;j++)
        {
            if(j!=i)
            {
                if((*pointer[j])>>7==1)
                {
                    MatrixINext[j]=_mm_xor_si128(MatrixINext[j],MatrixINext[i]);
                    ChoiceZero[i]=_mm_xor_si128(ChoiceZero[i], ChoiceZero[j]);
                }
            }
        }
        for(int j=0;j<84;j++)
            indicator[j]=_mm_slli_epi64(indicator[j],1);
    }
    
    for(int i=0;i<168;i+=2)
    {
        pointer[i]=(unsigned char *)&(indicator[84+i/2])+7;
        pointer[i+1]=(unsigned char *)&(indicator[84+i/2])+15;
    }
    for(int i=64;i<128;i++)
    {
        for(int j=0;j<168;j++)
        {
            if(j!=i)
            {
                if((*pointer[j])>>7==1)
                {
                    MatrixINext[j]=_mm_xor_si128(MatrixINext[j],MatrixINext[i]);
                    ChoiceZero[i]=_mm_xor_si128(ChoiceZero[i], ChoiceZero[j]);
                }
            }
        }
        for(int j=84;j<168;j++)
            indicator[j]=_mm_slli_epi64(indicator[j],1);
    }
}

void OTSet::PreTableGene()
{
    unsigned char d;
    for(int i=0;i<256;i++)
    {
        d=i;
        if((d & 1)==1)
        {
            for(int k=0;k<21;k++)
            {
                PreTable[256*k+i]=MatrixI[8*k];
                PreTableR[256*k+i]=MatrixR[8*k];
            }
        }
        else{
            for(int k=0;k<21;k++)
            {
                PreTable[256*k+i]=_mm_set_epi32(0,0,0,0);
                PreTableR[256*k+i]=_mm_set_epi32(0,0,0,0);
            }
        }
        d=d>>1;
        for(int j=1;j<8;j++)
        {
            if((d & 1)==1)
            {
                for(int k=0;k<21;k++)
                {
                    PreTable[256*k+i]=_mm_xor_si128(PreTable[256*k+i],MatrixI[8*k+j]);
                    PreTableR[256*k+i]=_mm_xor_si128(PreTableR[256*k+i],MatrixR[8*k+j]);
                }
            }
            d=d>>1;
        }
    }
}
void OTSet::BatchMulti_1(block *dst, block *src)
{
    block r1[168];
    block r2[168];
    uint16_t tmpi[168*8];
    uint8_t *tmp=(uint8_t *)tmpi;
    for(int i=0;i<84;i++)
        r1[i]=_mm_unpacklo_epi8(src[2*i],src[2*i+1]);
    for(int i=0;i<84;i++)
        r1[84+i]=_mm_unpackhi_epi8(src[2*i],src[2*i+1]);
    
    for(int i=0;i<42;i++)
        r2[i]=_mm_unpacklo_epi16(r1[2*i],r1[2*i+1]);
    for(int i=0;i<42;i++)
        r2[i+84]=_mm_unpacklo_epi16(r1[2*i+84],r1[2*i+1+84]);
    for(int i=0;i<42;i++)
        r2[i+42]=_mm_unpackhi_epi16(r1[2*i],r1[2*i+1]);
    for(int i=0;i<42;i++)
        r2[i+126]=_mm_unpackhi_epi16(r1[2*i+84],r1[2*i+1+84]);
    
    for(int i=0;i<21;i++)
        r1[i]=_mm_unpacklo_epi32(r2[2*i],r2[2*i+1]);
    for(int i=0;i<21;i++)
        r1[i+21]=_mm_unpackhi_epi32(r2[2*i],r2[2*i+1]);
    for(int i=0;i<21;i++)
        r1[i+42]=_mm_unpacklo_epi32(r2[2*i+42],r2[2*i+1+42]);
    for(int i=0;i<21;i++)
        r1[i+63]=_mm_unpackhi_epi32(r2[2*i+42],r2[2*i+1+42]);
    for(int i=0;i<21;i++)
        r1[i+84]=_mm_unpacklo_epi32(r2[2*i+84],r2[2*i+1+84]);
    for(int i=0;i<21;i++)
        r1[i+105]=_mm_unpackhi_epi32(r2[2*i+84],r2[2*i+1+84]);
    for(int i=0;i<21;i++)
        r1[i+126]=_mm_unpacklo_epi32(r2[2*i+126],r2[2*i+1+126]);
    for(int i=0;i<21;i++)
        r1[i+147]=_mm_unpackhi_epi32(r2[2*i+126],r2[2*i+1+126]);
    
    for(int i=0;i<168;i++)
        dst[i]=r1[i];
    
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<168;j++)
            tmpi[j+i*168]=_mm_movemask_epi8(r1[j]);
        for(int j=0;j<168;j++)
            r1[j]=_mm_slli_epi32(r1[j],1);
    }
    int id;
    for(int i=0;i<64;i++)
    {
        id=7-i/8+16*(i%8);
        dst[id]=PreTable[tmp[i*42]];
        for(int j=1;j<21;j++)
        {
            dst[id]=_mm_xor_si128(dst[id],PreTable[tmp[2*j+i*42]+(j<<8)]);
        }
        id=id+8;
        dst[id]=PreTable[tmp[i*42+1]];
        for(int j=1;j<21;j++)
            dst[id]=_mm_xor_si128(dst[id],PreTable[tmp[2*j+i*42+1]+(j<<8)]);
    }
}
void OTSet::BatchMulti_2(block *dst, block *src)
{
    block r1[168];
    block r2[168];
    uint16_t tmpi[168*8];
    uint8_t *tmp=(uint8_t *)tmpi;
    for(int i=0;i<84;i++)
        r1[i]=_mm_unpacklo_epi8(src[2*i],src[2*i+1]);
    for(int i=0;i<84;i++)
        r1[84+i]=_mm_unpackhi_epi8(src[2*i],src[2*i+1]);
    
    for(int i=0;i<42;i++)
        r2[i]=_mm_unpacklo_epi16(r1[2*i],r1[2*i+1]);
    for(int i=0;i<42;i++)
        r2[i+84]=_mm_unpacklo_epi16(r1[2*i+84],r1[2*i+1+84]);
    for(int i=0;i<42;i++)
        r2[i+42]=_mm_unpackhi_epi16(r1[2*i],r1[2*i+1]);
    for(int i=0;i<42;i++)
        r2[i+126]=_mm_unpackhi_epi16(r1[2*i+84],r1[2*i+1+84]);
    
    for(int i=0;i<21;i++)
        r1[i]=_mm_unpacklo_epi32(r2[2*i],r2[2*i+1]);
    for(int i=0;i<21;i++)
        r1[i+21]=_mm_unpackhi_epi32(r2[2*i],r2[2*i+1]);
    for(int i=0;i<21;i++)
        r1[i+42]=_mm_unpacklo_epi32(r2[2*i+42],r2[2*i+1+42]);
    for(int i=0;i<21;i++)
        r1[i+63]=_mm_unpackhi_epi32(r2[2*i+42],r2[2*i+1+42]);
    for(int i=0;i<21;i++)
        r1[i+84]=_mm_unpacklo_epi32(r2[2*i+84],r2[2*i+1+84]);
    for(int i=0;i<21;i++)
        r1[i+105]=_mm_unpackhi_epi32(r2[2*i+84],r2[2*i+1+84]);
    for(int i=0;i<21;i++)
        r1[i+126]=_mm_unpacklo_epi32(r2[2*i+126],r2[2*i+1+126]);
    for(int i=0;i<21;i++)
        r1[i+147]=_mm_unpackhi_epi32(r2[2*i+126],r2[2*i+1+126]);
    
    for(int i=0;i<168;i++)
        dst[i]=r1[i];
    
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<168;j++)
            tmpi[j+i*168]=_mm_movemask_epi8(r1[j]);
        for(int j=0;j<168;j++)
            r1[j]=_mm_slli_epi32(r1[j],1);
    }
    int id;
    for(int i=0;i<64;i++)
    {
        id=7-i/8+16*(i%8);
        dst[id]=PreTableR[tmp[i*42]];
        for(int j=1;j<21;j++)
        {
            dst[id]=_mm_xor_si128(dst[id],PreTableR[tmp[2*j+i*42]+(j<<8)]);
        }
        id=id+8;
        dst[id]=PreTableR[tmp[i*42+1]];
        for(int j=1;j<21;j++)
            dst[id]=_mm_xor_si128(dst[id],PreTableR[tmp[2*j+i*42+1]+(j<<8)]);
    }
}
void OTSet::ExtractChoiceZero()
{
    block tmp[11];
    unsigned char *p1,*p2;
    for(int i=0;i<10;i++)
    {
        p1=(unsigned char*)&(tmp[i]);
        for(int j=0;j<8;j++)
        {
            p2=(unsigned char*)(&(ChoiceZero[i*16+j]));
            p1[j]=p2[0];
        }
        for(int j=8;j<16;j++)
        {
            p2=(unsigned char*)(&(ChoiceZero[i*16+j]));
            p1[j]=p2[0];
        }
    }
    
    p1=(unsigned char*)(&tmp[10]);
    for(int j=0;j<8;j++)
    {
        p2=(unsigned char*)(&ChoiceZero[160+j]);
        p1[j]=p2[0];
    }
    for(int j=8;j<16;j++)
        p1[j]=0;
    
    NewLabels(OTEChoice,OTBufferSize/128);
    NewLabels(OTEChoice+OTBufferSize/128+1,1);
    
    OTEChoice[OTBufferSize/128]=_mm_set_epi16(_mm_movemask_epi8(tmp[7]),_mm_movemask_epi8(tmp[6]),_mm_movemask_epi8(tmp[5]),_mm_movemask_epi8(tmp[4]),_mm_movemask_epi8(tmp[3]),_mm_movemask_epi8(tmp[2]),_mm_movemask_epi8(tmp[1]),_mm_movemask_epi8(tmp[0]));
    uint16_t *p=(uint16_t *)&(OTEChoice[OTBufferSize/128+1]);
    
    p[0]=_mm_movemask_epi8(tmp[8]);
    p[1]=_mm_movemask_epi8(tmp[9]);
    p[2]=_mm_movemask_epi8(tmp[10]);
}
void OTSet::ExtractBaseOT()
{
    for(int i=0;i<168;i++)
        BaseOTChoice[i]=(_mm_extract_epi8(ChoiceZero[i],0)>0);
    block tmp[128];
    Transpose(tmp,ChoiceZero);
    GDelta[0]=tmp[0];
    Transpose(tmp,ChoiceZero+128);
    GDelta[1]=_mm_andnot_si128(CCheckIndex[40],tmp[0]);
}
double OTPTime=0;
double CCTime=0;

void OTSet::OTExtension1(block *dst)
{
    OTNum+=1;
    OTCount+=OTBufferSize;
    block tmp;
    for(int j=0;j<size;j++)
    {
        tmp=_mm_set_epi32(0,0,0,Public_Count+j);
        for(int i=0;i<168;i++)
        {
            OTEtemp[j*168+i]=_mm_xor_si128(tmp,BaseOTRec[i]);
        }
    }
    for(int j=0;j<size;j++)
    {
        tmp=_mm_set_epi32(0,0,0,Public_Count+j);
        for(int i=0;i<168;i++)
        {
            OTEtemp[j*168+i+168*(size)]=_mm_xor_si128(tmp,BaseOTSend[i][0]);
        }
    }
    for(int j=0;j<size;j++)
    {
        tmp=_mm_set_epi32(0,0,0,Public_Count+j);
        for(int i=0;i<168;i++)
        {
            OTEtemp[j*168+i+168*(size)*2]=_mm_xor_si128(tmp,BaseOTSend[i][1]);
        }
    }
    AES_ecb_encrypt_blks(OTEtemp,168*(size)*3,&Public_AES_KEY);
    for(int j=0;j<size;j++)
    {
        tmp=_mm_set_epi32(0,0,0,Public_Count+j);
        for(int i=0;i<168;i++)
        {
            OTEtemp[j*168+i]=_mm_xor_si128(OTEtemp[j*168+i],_mm_xor_si128(tmp,BaseOTRec[i]));
        }
    }
    for(int j=0;j<size;j++)
    {
        tmp=_mm_set_epi32(0,0,0,Public_Count+j);
        for(int i=0;i<168;i++)
        {
            OTEtemp[j*168+i+168*(size)]=_mm_xor_si128(OTEtemp[j*168+i+168*(size)],_mm_xor_si128(tmp,BaseOTSend[i][0]));
        }
    }
    for(int j=0;j<size;j++)
    {
        tmp=_mm_set_epi32(0,0,0,Public_Count+j);
        for(int i=0;i<168;i++)
        {
            OTEtemp[j*168+i+168*(size)*2]=_mm_xor_si128(OTEtemp[j*168+i+168*(size)*2],_mm_xor_si128(tmp,BaseOTSend[i][1]));
        }
    }
    Public_Count+=size;
    for(int j=0;j<size;j++)
    {
        for(int i=0;i<168;i++)
        {
            OTEtemp[j*168+i+168*(size)*2]=_mm_xor_si128(_mm_xor_si128(OTEtemp[j*168+i+168*(size)*2],OTEtemp[j*168+i+168*(size)]),OTEChoice[j]);
        }
    }
    
}
void OTSet::OTExtension2(block *dst)
{
    PreTableGene();
    for(int i=0;i<168;i++)
    {
        if(BaseOTChoice[i]==1)
        {
            for(int j=0;j<size;j++)
            {
                OTEtemp[j*168+i+168*(size)*2]=_mm_xor_si128(OTEtemp[j*168+i+168*(size)*3],OTEtemp[j*168+i]);
            }
        }
        else
        {
            for(int j=0;j<size;j++)
            {
                OTEtemp[j*168+i+168*(size)*2]=OTEtemp[j*168+i];
            }
        }
    }
    for(int i=0;i<OTBufferSize/128;i++)
        BatchMulti_1(dst+128*i,OTEtemp+i*168+168*size*2);
    for(int i=0;i<OTBufferSize/128;i++)
        BatchMulti_2(dst+128*i+OTBufferSize,OTEtemp+i*168+168*size);
    BatchMulti_1(BaseOTTemp,OTEtemp+OTBufferSize/128*168+168*size*2);
    BatchMulti_1(BaseOTTemp+128,OTEtemp+OTBufferSize/128*168+168*size*2+168);
    BatchMulti_2(BaseOTTemp+256,OTEtemp+OTBufferSize/128*168+168*size);
    BatchMulti_2(BaseOTTemp+384,OTEtemp+OTBufferSize/128*168+168*size+168);
    for(int i=0;i<168;i++)
    {
        BaseOTRec[i]=BaseOTTemp[256+i];
        BaseOTSend[i][0]=BaseOTTemp[i];
        BaseOTSend[i][1]=_mm_xor_si128(BaseOTTemp[i],Delta);
    }
}
void OTSet::OTExtension3(block *dst)
{
    for(int i=0;i<OTBufferSize;i++)
    {
        dst[i]=_mm_and_si128(dst[i],bed1);
        dst[i+OTBufferSize]=_mm_and_si128(dst[i+OTBufferSize],bed1);
    }
    for(int i=0;i<OTBufferSize/128;i++)
    {
        memset(BaseOTTemp,0,128*16);
        BaseOTTemp[128]=OTEChoice[i];
        LSTranspose(BaseOTTemp,BaseOTTemp+128);
        for(int j=0;j<128;j++)
        {
            dst[j+OTBufferSize+i*128]=_mm_xor_si128(dst[j+OTBufferSize+i*128],BaseOTTemp[j]);
        }
        
    }
}
void OTSet::OTExtension4(block *dst)
{
    ExtractBaseOT();
    memcpy(MatrixI,MatrixINext,16*168);
    MatrixISetup();
    GarbleMatrix();
    ExtractChoiceZero();
}
void OTSet::ConsistencyCheck1()
{
    NewLabels(&seed,1);
}
void OTSet::ConsistencyCheck2()
{
    AES_set_encrypt_key(seed,&LKey);
    AES_set_encrypt_key(seedR,&RKey);
    for(int i=0;i<OTBufferSize+256;i++)
        ChiThis[i]=_mm_set_epi32(0,0,0,i);
    for(int i=0;i<OTBufferSize+256;i++)
        ChiThis[i+OTBufferSize+256]=_mm_set_epi32(0,0,0,i);
    for(int i=0;i<OTBufferSize+256;i++)
        ChiThis[i+(OTBufferSize+256)*2]=_mm_set_epi32(0,0,0,i);
    AES_ecb_encrypt_blks(ChiThis,OTBufferSize+256,&LKey);
    AES_ecb_encrypt_blks(ChiThat,OTBufferSize+256,&LKey);
    for(int i=0;i<OTBufferSize+256;i++)
        ChiThis[i]=_mm_xor_si128(ChiThis[i],ChiThis[i+(OTBufferSize+256)]);
    for(int i=0;i<OTBufferSize+256;i++)
        ChiThat[i]=_mm_xor_si128(ChiThat[i],ChiThis[i+(OTBufferSize+256)]);
    mul128(OTBuffer[0], ChiThis[0], &(q[0]), &(q[1]));
    for(int i=1;i<OTBufferSize;i++)
    {
        mul128(OTBuffer[i], ChiThis[i], &tmp1, &tmp2);
        q[0]=_mm_xor_si128(q[0],tmp1);
        q[1]=_mm_xor_si128(q[1],tmp2);
    }
    for(int i=0;i<256;i++)
    {
        mul128(BaseOTTemp[i], ChiThis[OTBufferSize+i], &tmp1, &tmp2);
        q[0]=_mm_xor_si128(q[0],tmp1);
        q[1]=_mm_xor_si128(q[1],tmp2);
    }
    mul128(OTBuffer[OTBufferSize], ChiThat[0], &(t[0]), &(t[1]));
    for(int i=1;i<OTBufferSize;i++)
    {
        mul128(OTBuffer[i+OTBufferSize], ChiThat[i], &tmp1, &tmp2);
        t[0]=_mm_xor_si128(t[0],tmp1);
        t[1]=_mm_xor_si128(t[1],tmp2);
    }
    for(int i=0;i<256;i++)
    {
        mul128(BaseOTTemp[i+256], ChiThat[OTBufferSize+i], &tmp1, &tmp2);
        t[0]=_mm_xor_si128(t[0],tmp1);
        t[1]=_mm_xor_si128(t[1],tmp2);
    }
    x=_mm_set_epi32(0,0,0,0);
    uint8_t *cp=NULL;
    for(int i=0;i<OTBufferSize/128+2;i++)
    {
        cp=(uint8_t*)&(OTEChoice[i]);
        for(int j=0;j<8;j++)
        {
            for(int k=0;k<16;k++)
            {
                if((cp[k]&1)==1)x=_mm_xor_si128(x,ChiThat[k*8+j+i*128]);
            }
        }
        OTEChoice[i]=_mm_srli_epi16(OTEChoice[i],1);
    }
}
void OTSet::ConsistencyCheck3()
{
    mul128(X,Delta,&tmp1, &tmp2);
    tt[0]=_mm_xor_si128(tt[0],tmp1);
    tt[1]=_mm_xor_si128(tt[1],tmp2);
    tt[0]=_mm_xor_si128(tt[0],q[0]);
    tt[1]=_mm_xor_si128(tt[1],q[1]);
    if(_mm_testz_si128(tt[0],All1)==0)
    {
        printf("Test error!\n");
        exit(0);
    }
    if(_mm_testz_si128(tt[1],All1)==0)
    {
        printf("Test error!\n");
        exit(0);
    }
}
/*
void OTSet::ConsistencyCheck()
{
    ConsistencyCheck1();
    exchange(&seedR,&seed,16);
    ConsistencyCheck2();
    exchange(&X,tt,&x,t,16,32);
    ConsistencyCheck3();
}
 */
void OTSet::DeltaConsistencyCheck1()
{
    tmp[0]=_mm_and_si128(OTEChoice[OTBufferSize/128+1],DeltaCheckBlock);
    t0=tmp[0];
    tmp[0]=_mm_xor_si128(tmp[0],DeltaCheckChoice);
    //exchange(&tmp[1],&tmp[0],16);
}
void OTSet::DeltaConsistencyCheck2()
{
    memset(tmpd,0,256*16);
    for(int i=0;i<128;i++)
        tmpd[i]=_mm_and_si128(MatrixDelta[i],tmp[1]);
    Transpose(tmpd+128,tmpd);
    for(int i=0;i<40;i++)
        tmpd[i+40]=_mm_xor_si128(_mm_xor_si128(BaseOTTemp[i+176],DeltaCheck[i+40]),tmpd[176+i]);
    for(int i=0;i<40;i++)
        tmpd[i]=_mm_xor_si128(BaseOTTemp[256+i+176],DeltaCheck[i]);
    SHA256((unsigned char*)tmpd,40*16,hash);
    SHA256((unsigned char*)&(tmpd[40]),40*16,&(hash[SHA256_DIGEST_LENGTH]));
}

void OTSet::DeltaConsistencyCheck3()
{
    for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
        if((hash[i+2*SHA256_DIGEST_LENGTH]^hash[i])!=0)
        {
            printf("test error!");
            exit(0);
        }
    for(int i=0;i<40;i++)
    {
        DeltaCheck[i+40]=BaseOTTemp[i+176];
        DeltaCheck[i]=BaseOTTemp[i+256+176];
    }
    DeltaCheckChoice=t0;
}
