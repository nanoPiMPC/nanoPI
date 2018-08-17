//
//  Stage.cpp
//
//
//  Created by Sourgroup on 11/17/17.
//

#include "Stage.hpp"
long long Stage_Count=0;
#ifdef StageMeasure
double Total_Time=0;
time_point<high_resolution_clock> StageTimer;
#endif
MStage S;
void MStage::Setup(int id,uint32_t MStgSize,MPool *P,wiremap *M)
{
    ANDCount=0;
    XORCount=0;
    MyID=id;
    MP=P;
    StageMap=M;
    IO=P->IO;
    MStageSize=MStgSize;
    index=0;
    release_index=0;
    P->Flip(StageMap->Read(StageMap->MapSize+1));
    SolderRecord=(unsigned char*)malloc(sizeof(unsigned char)*MStageSize*(1+PartyNumber));
    release_record=(Index *)malloc(sizeof(Index)*blowup*MStageSize);
    queue=(Gate_Record*)malloc(sizeof(Gate_Record)*MStageSize*blowup);
    if(MyID==0)
    {
        receivedgarbledrow=(block *)_mm_malloc(sizeof(block)*((PartyNumber-1)*PartyNumber*4*MStageSize/*GarbledRow*/+2*(PartyNumber-1)*MStageSize/*OAuthBit*/+2*(PartyNumber-1)*3*MStageSize/*Tuples*/+2*(PartyNumber-1)*4*MStageSize/*LAuthBit*/+MStageSize/*Label0*/+(PartyNumber-1)*MStageSize*2/*SolderingProveBuffer*/+MStageSize*2/*SolderingVerifyBuffer*/+MStageSize*2/*SolderingProvePRG*/),16);
        OAuthBit=receivedgarbledrow+(PartyNumber-1)*PartyNumber*4*MStageSize;
        
    }
    else
    OAuthBit=(block *)_mm_malloc(sizeof(block)*(2*(PartyNumber-1)*MStageSize/*OAuthBit*/+2*(PartyNumber-1)*3*MStageSize/*Tuples*/+2*(PartyNumber-1)*4*MStageSize/*LAuthBit*/+MStageSize/*Label0*/+2*PartyNumber*4*MStageSize/*AESPack*/+(PartyNumber-1)*MStageSize*2/*SolderingProveBuffer*/+MStageSize*2/*SolderingVerifyBuffer*/+MStageSize*2/*SolderingProvePRG*/),16);
    Tuples=OAuthBit+2*(PartyNumber-1)*MStageSize;
    LAuthBit=Tuples+2*(PartyNumber-1)*3*MStageSize;
    Label0=LAuthBit+2*(PartyNumber-1)*4*MStageSize;
    if(MyID!=0)
    {
        AESPack=Label0+MStageSize;
        SolderingProveBuffer=AESPack+2*PartyNumber*4*MStageSize;
    }
    else
        SolderingProveBuffer=Label0+MStageSize;
    SolderingVerifyBuffer=SolderingProveBuffer+2*(PartyNumber-1)*MStageSize;
    rcoe=SolderingVerifyBuffer+MStageSize*2;
    block tmp=_mm_set_epi32(1,2,3,4);
    AES_set_encrypt_key(tmp,&Public_AES_KEY);
    Public_Count=0;
    AndSum=MStageSize;
#ifdef StageMeasure
    Stage_Count=0;
    StageTimer=clock_start();
#endif
    reset();
}
void MStage::Close()
{
    exec();
    reset();
    free(release_record);
    free(queue);
    free(SolderRecord);
    if(MyID==0)
        _mm_free(receivedgarbledrow);
    else
    _mm_free(OAuthBit);
}
void MStage::reset()
{
#ifdef StageMeasure
    double t1=time_from(StageTimer);
   // Total_Time+=t1;
   // printf("Stage: %d Total gates: %lld AND Gates Avg Speed: %lld %lf %lf\n",index,AndSum,Stage_Count*MStageSize,Total_Time/1000000,(Stage_Count*MStageSize/(Total_Time/1000000)));
    printf("Execute time %lf\n",t1/1000000);
#endif
#ifdef StageMeasure
    StageTimer=clock_start();
#endif
    ReleaseAll();
    index=0;
    release_index=0;
    MP->NewBits(OAuthBit,AndSum);
    MP->NewTuples(Tuples,AndSum);
    if(MyID!=0)
        MP->NewLabels(Label0,MStageSize);
    AndSum=0;
}
void MStage::andpre(wire *o, wire *l, wire *r)
{
    ANDCount++;
    queue[index].o=o;
    queue[index].l=l;
    queue[index].r=r;
    queue[index].type=0;
    for(int i=0;i<2*(PartyNumber-1);i++)
        o->AuthBit[i]=OAuthBit[AndSum*2*(PartyNumber-1)+i];
    unsigned char solder=0;
#ifdef Naive
    block Soldertmp[PartyNumber*4];
    void *exsrc[PartyNumber],*exdst[PartyNumber];
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(Soldertmp[2*i+2*PartyNumber]);
        exdst[i]=&(Soldertmp[2*i]);
        if(i<MyID)
        {
            Soldertmp[2*i+2*PartyNumber]=_mm_xor_si128(l->AuthBit[2*i],Tuples[AndSum*3*2*(PartyNumber-1)+2*i]);
            Soldertmp[2*i+2*PartyNumber+1]=_mm_xor_si128(r->AuthBit[2*i],Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)+2*i]);
        }
        if(i>MyID)
        {
            Soldertmp[2*i+2*PartyNumber]=_mm_xor_si128(l->AuthBit[2*(i-1)],Tuples[AndSum*3*2*(PartyNumber-1)+2*(i-1)]);
            Soldertmp[2*i+1+2*PartyNumber]=_mm_xor_si128(r->AuthBit[2*(i-1)],Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)+2*(i-1)]);
        }
    }
    Exchange(IO,exdst,exsrc,2*sizeof(block));
    Soldertmp[2*MyID]=_mm_xor_si128(l->AuthBit[0],Tuples[AndSum*3*2*(PartyNumber-1)]);
    Soldertmp[2*MyID+1]=_mm_xor_si128(r->AuthBit[0],Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)]);
    for(int i=1;i<PartyNumber;i++)
    {
        Soldertmp[0]=_mm_xor_si128(Soldertmp[0],Soldertmp[2*i]);
        Soldertmp[1]=_mm_xor_si128(Soldertmp[1],Soldertmp[2*i+1]);
    }
    
    if(extract_bit(Soldertmp[0])!=0)solder=2;
    if(extract_bit(Soldertmp[1])!=0)solder^=1;
    SolderRecord[AndSum]=solder;
#else
    if((extract_bit(l->AuthBit[0])^extract_bit(Tuples[AndSum*3*2*(PartyNumber-1)]))==1)
        solder=2;
    if((extract_bit(r->AuthBit[0])^extract_bit(Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)]))==1)
        solder^=1;
    SolderRecord[MyID*MStageSize+AndSum]=solder;
    for(int i=0;i<PartyNumber-1;i++)
    {
        SolderingProveBuffer[2*MStageSize*i+2*AndSum]=_mm_xor_si128(l->AuthBit[2*i],Tuples[AndSum*3*2*(PartyNumber-1)+2*i]);
        SolderingProveBuffer[2*MStageSize*i+2*AndSum+1]=_mm_xor_si128(r->AuthBit[2*i],Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)+2*i]);
    }
    SolderingVerifyBuffer[2*AndSum]=_mm_xor_si128(l->AuthBit[1],Tuples[AndSum*3*2*(PartyNumber-1)+1]);
    SolderingVerifyBuffer[2*AndSum+1]=_mm_xor_si128(r->AuthBit[1],Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)+1]);
    for(int i=1;i<PartyNumber-1;i++)
    {
        SolderingVerifyBuffer[2*AndSum]=_mm_xor_si128(SolderingVerifyBuffer[2*AndSum],_mm_xor_si128(l->AuthBit[2*i+1],Tuples[AndSum*3*2*(PartyNumber-1)+2*i+1]));
        SolderingVerifyBuffer[2*AndSum+1]=_mm_xor_si128(SolderingVerifyBuffer[2*AndSum+1],_mm_xor_si128(r->AuthBit[2*i+1],Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)+2*i+1]));
    }
#endif
    
    if(MyID==0)
    {
        AuthBitXor(&LAuthBit[AndSum*4*2*(PartyNumber-1)],&OAuthBit[AndSum*2*(PartyNumber-1)],&Tuples[AndSum*3*2*(PartyNumber-1)+4*(PartyNumber-1)]);
        AuthBitXor(&LAuthBit[AndSum*4*2*(PartyNumber-1)+2*(PartyNumber-1)],&LAuthBit[AndSum*4*2*(PartyNumber-1)],&Tuples[AndSum*3*2*(PartyNumber-1)]);
        AuthBitXor(&LAuthBit[AndSum*4*2*(PartyNumber-1)+4*(PartyNumber-1)],&LAuthBit[AndSum*4*2*(PartyNumber-1)],&Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)]);
    AuthBitXor(&LAuthBit[AndSum*4*2*(PartyNumber-1)+6*(PartyNumber-1)],&LAuthBit[AndSum*4*2*(PartyNumber-1)+2*(PartyNumber-1)],&Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)]);
        for(int i=0;i<PartyNumber-1;i++)
            LAuthBit[AndSum*4*2*(PartyNumber-1)+6*(PartyNumber-1)+2*i]=_mm_xor_si128(LAuthBit[AndSum*4*2*(PartyNumber-1)+6*(PartyNumber-1)+2*i],MP->plainbit1);
    }
    else
    {
        o->Label[0]=Label0[AndSum];
        AuthBitXor(&LAuthBit[AndSum*4*2*(PartyNumber-1)],&OAuthBit[AndSum*2*(PartyNumber-1)],&Tuples[AndSum*3*2*(PartyNumber-1)+4*(PartyNumber-1)]);
        AuthBitXor(&LAuthBit[AndSum*4*2*(PartyNumber-1)+2*(PartyNumber-1)],&LAuthBit[AndSum*4*2*(PartyNumber-1)],&Tuples[AndSum*3*2*(PartyNumber-1)]);
        AuthBitXor(&LAuthBit[AndSum*4*2*(PartyNumber-1)+4*(PartyNumber-1)],&LAuthBit[AndSum*4*2*(PartyNumber-1)],&Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)]);
        AuthBitXor(&LAuthBit[AndSum*4*2*(PartyNumber-1)+6*(PartyNumber-1)],&LAuthBit[AndSum*4*2*(PartyNumber-1)+2*(PartyNumber-1)],&Tuples[AndSum*3*2*(PartyNumber-1)+2*(PartyNumber-1)]);
        LAuthBit[AndSum*4*2*(PartyNumber-1)+6*(PartyNumber-1)+1]=
        _mm_xor_si128(LAuthBit[AndSum*4*2*(PartyNumber-1)+6*(PartyNumber-1)+1],MP->delta);
    }
    index++;
    AndSum++;
    if((index>=MStageSize*5)||(AndSum>=MStageSize)){
        exec();
        reset();
    }
}
void MStage::xorpre(wire *o, wire *l, wire *r)
{
    XORCount++;
    queue[index].o=o;
    queue[index].l=l;
    queue[index].r=r;
    queue[index].type=1;
    for(int i=0;i<2*(PartyNumber-1);i++)
        o->AuthBit[i]=_mm_xor_si128(l->AuthBit[i],r->AuthBit[i]);
    if(MyID!=0)
    {
        o->Label[0]=_mm_xor_si128(l->Label[0],r->Label[0]);
    }
    index++;
    if((index>=MStageSize*5)||(AndSum>=MStageSize)){
        exec();
        reset();
    }
}
void MStage::copypre(wire *dst, wire *src)
{
    queue[index].o=dst;
    queue[index].l=src;
    queue[index].type=2;
    for(int i=0;i<2*(PartyNumber-1);i++)
        dst->AuthBit[i]=src->AuthBit[i];
    if(MyID!=0)
    {
        dst->Label[0]=src->Label[0];
    }
    index++;
    if((index>=MStageSize*5)||(AndSum>=MStageSize)){
        exec();
        reset();
    }
}
void MStage::Solder()
#ifdef Naive
{
    
}
#else
{
    void *exsrc[PartyNumber],*exdst[PartyNumber];
    for(int i=0;i<PartyNumber;i++)
    {
        exsrc[i]=&(SolderRecord[MyID*MStageSize]);
        exdst[i]=&(SolderRecord[i*MStageSize]);
    }
    Exchange(IO,exdst,exsrc,AndSum);

    for(int j=0;j<AndSum;j++)
        SolderRecord[MStageSize*PartyNumber+j]=0;
    for(int i=0;i<PartyNumber;i++)
    {
        if(i!=MyID)
            for(int j=0;j<AndSum;j++)
            {
                SolderRecord[MStageSize*PartyNumber+j]^=SolderRecord[MStageSize*i+j];
            }
    }
    for(int i=0;i<AndSum;i++)
    {
        if((SolderRecord[MStageSize*PartyNumber+i] & 2)==2)
            SolderingVerifyBuffer[2*i]=_mm_xor_si128(SolderingVerifyBuffer[2*i],MP->Delta);
        if((SolderRecord[MStageSize*PartyNumber+i] & 1)==1)
            SolderingVerifyBuffer[2*i+1]=_mm_xor_si128(SolderingVerifyBuffer[2*i+1],MP->Delta);
    }
    
    block seed[PartyNumber];
    MP->NewLabels(seed+MyID,1);
    void *seedexsrc[PartyNumber],*seedexdst[PartyNumber];
    for(int i=0;i<PartyNumber;i++)
    {
        seedexsrc[i]=seed+MyID;
        seedexdst[i]=seed+i;
    }
    Exchange(IO,seedexdst,seedexsrc,16);

    for(int i=1;i<PartyNumber;i++)
        seed[0]=_mm_xor_si128(seed[0],seed[i]);
    AES_KEY tmpkey;
    AES_set_encrypt_key(seed[0],&tmpkey);
    PRG(rcoe,MStageSize*2,&(tmpkey),&(Public_Count));
    block results[2*PartyNumber];
    block tmp[4];

    
    for(int i=0;i<PartyNumber;i++)
    {
        if(i<MyID)
        {
            mul128(SolderingProveBuffer[i*2*MStageSize],rcoe[0],&(results[2*i]),&(results[2*i+1]));
            for(int j=1;j<2*AndSum;j++)
            {
                mul128(SolderingProveBuffer[i*2*MStageSize+j],rcoe[j],&(tmp[0]),&(tmp[1]));
                results[2*i]=_mm_xor_si128(results[2*i],tmp[0]);
                results[2*i+1]=_mm_xor_si128(results[2*i],tmp[1]);
            }
        }
        if(i==MyID)
        {
            mul128(SolderingVerifyBuffer[0],rcoe[0],&(results[2*i]),&(results[2*i+1]));
            for(int j=1;j<2*AndSum;j++)
            {
                mul128(SolderingVerifyBuffer[j],rcoe[j],&(tmp[0]),&(tmp[1]));
                results[2*i]=_mm_xor_si128(results[2*i],tmp[0]);
                results[2*i+1]=_mm_xor_si128(results[2*i],tmp[1]);
            }
        }
        if(i>MyID)
        {
            mul128(SolderingProveBuffer[(i-1)*2*MStageSize],rcoe[0],&(results[2*i]),&(results[2*i+1]));
            for(int j=1;j<2*AndSum;j++)
            {
                mul128(SolderingProveBuffer[(i-1)*2*MStageSize+j],rcoe[j],&(tmp[0]),&(tmp[1]));
                results[2*i]=_mm_xor_si128(results[2*i],tmp[0]);
                results[2*i+1]=_mm_xor_si128(results[2*i],tmp[1]);
            }
        }
    }
    
    void *solderprovesrc[PartyNumber],*solderprovedst[PartyNumber];
    block soldertmp[PartyNumber*2];
    for(int i=0;i<PartyNumber;i++)
    {
        solderprovesrc[i]=&(results[2*i]);
        solderprovedst[i]=&(soldertmp[2*i]);
    }
    Exchange(IO,solderprovedst,solderprovesrc,32);

    soldertmp[2*MyID]=results[2*MyID];
    soldertmp[2*MyID+1]=results[2*MyID+1];
    tmp[0]=soldertmp[0];
    tmp[1]=soldertmp[1];
    for(int i=1;i<PartyNumber;i++)
    {
        tmp[0]=_mm_xor_si128(tmp[0],soldertmp[2*i]);
        tmp[1]=_mm_xor_si128(tmp[1],soldertmp[2*i+1]);
    }
    if((_mm_testz_si128(tmp[0],MP->all1)!=1) || (_mm_testz_si128(tmp[1],MP->all1)!=1))
    {
        print(tmp[0]);
        print(tmp[1]);
        error("Soldering Error\n");
    }
    for(int i=0;i<AndSum;i++)
    {
        SolderRecord[i]=SolderRecord[MStageSize*PartyNumber+i]^SolderRecord[MStageSize*MyID+i];
    }
}
#endif
void MStage::Garbling()
{
    if(MyID==0) return;
    block tmp[5];
    int id=0;
    for(int i=0;i<index;i++)
    {
        if(queue[i].type==0)
        {
            if((SolderRecord[id] & 2)==0)
            {
                tmp[1]=_mm_and_si128(_mm_xor_si128(*queue[i].l->Label,MP->Delta),MP->bed1);
                tmp[0]=_mm_and_si128(*queue[i].l->Label,MP->bed1);
            }
            else
            {
                tmp[0]=_mm_and_si128(_mm_xor_si128(*queue[i].l->Label,MP->Delta),MP->bed1);
                tmp[1]=_mm_and_si128(*queue[i].l->Label,MP->bed1);
            }
            if((SolderRecord[id] & 1)==0)
            {
                tmp[3]=_mm_and_si128(_mm_xor_si128(*queue[i].r->Label,MP->Delta),MP->bed1);
                tmp[2]=_mm_and_si128(*queue[i].r->Label,MP->bed1);
            }
            else
            {
                tmp[2]=_mm_and_si128(_mm_xor_si128(*queue[i].r->Label,MP->Delta),MP->bed1);
                tmp[3]=_mm_and_si128(*queue[i].r->Label,MP->bed1);
            }
            tmp[2]=_mm_slli_si128(tmp[2],1);
            tmp[3]=_mm_slli_si128(tmp[3],1);
            AESPack[4*PartyNumber*id]=_mm_xor_si128(tmp[0],tmp[2]);
            AESPack[4*PartyNumber*id+PartyNumber]=_mm_xor_si128(tmp[0],tmp[3]);
            AESPack[4*PartyNumber*id+PartyNumber*2]=_mm_xor_si128(tmp[1],tmp[2]);
            AESPack[4*PartyNumber*id+PartyNumber*3]=_mm_xor_si128(tmp[1],tmp[3]);
            for(int j=1;j<PartyNumber;j++)
            {
                tmp[4]=_mm_set_epi32(0,0,i,j);
                AESPack[4*PartyNumber*id+j]=_mm_xor_si128(AESPack[4*PartyNumber*id],tmp[4]);
                AESPack[4*PartyNumber*id+j+PartyNumber]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber],tmp[4]);
                AESPack[4*PartyNumber*id+j+PartyNumber*2]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*2],tmp[4]);
                AESPack[4*PartyNumber*id+j+PartyNumber*3]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*3],tmp[4]);
            }
            tmp[4]=_mm_set_epi32(0,0,i,0);
            AESPack[4*PartyNumber*id]=_mm_xor_si128(AESPack[4*PartyNumber*id],tmp[4]);
            AESPack[4*PartyNumber*id+PartyNumber]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber],tmp[4]);
            AESPack[4*PartyNumber*id+PartyNumber*2]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*2],tmp[4]);
            AESPack[4*PartyNumber*id+PartyNumber*3]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*3],tmp[4]);
            id++;
        }
    }
    memcpy(&(AESPack[4*PartyNumber*MStageSize]),AESPack,4*PartyNumber*AndSum*16);
    AES_ecb_encrypt_blks(AESPack,4*PartyNumber*AndSum,&Public_AES_KEY);
    for(int i=0;i<4*PartyNumber*AndSum;i++)
        AESPack[i]=_mm_xor_si128(AESPack[i],AESPack[i+4*PartyNumber*MStageSize]);
}
void MStage::exec()
{
#ifdef StageMeasure
    Stage_Count++;
    printf("Stage: %lld\n",Stage_Count);
#endif
    Solder();
    Garbling();
    Eval();
}
void MStage::Eval()
{
    if(MyID!=0)
    {
        void *gathersrc;
        int id=0;
        for(int i=0;i<index;i++)
        {
            if(queue[i].type==0)
            {
                AESPack[4*PartyNumber*id+PartyNumber-1]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber-1],Label0[id]);
                AESPack[4*PartyNumber*id+PartyNumber*2-1]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*2-1],Label0[id]);
                AESPack[4*PartyNumber*id+PartyNumber*3-1]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*3-1],Label0[id]);
                AESPack[4*PartyNumber*id+PartyNumber*4-1]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*4-1],Label0[id]);
                if(extract_bit(LAuthBit[id*4*2*(PartyNumber-1)])==1)
                    AESPack[4*PartyNumber*id+PartyNumber-1]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber-1],MP->Delta);
                if(extract_bit(LAuthBit[id*4*2*(PartyNumber-1)+2*(PartyNumber-1)])==1)
                    AESPack[4*PartyNumber*id+PartyNumber*2-1]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*2-1],MP->Delta);
                if(extract_bit(LAuthBit[id*4*2*(PartyNumber-1)+4*(PartyNumber-1)])==1)
                    AESPack[4*PartyNumber*id+PartyNumber*3-1]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*3-1],MP->Delta);
                if(extract_bit(LAuthBit[id*4*2*(PartyNumber-1)+6*(PartyNumber-1)])==1)
                    AESPack[4*PartyNumber*id+PartyNumber*4-1]=_mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*4-1],MP->Delta);
                for(int j=0;j<PartyNumber-1;j++)
                {
                    AESPack[4*PartyNumber*id+PartyNumber-1]=
                    _mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber-1],
                                  LAuthBit[id*4*2*(PartyNumber-1)+j*2+1]);
                    AESPack[4*PartyNumber*id+PartyNumber*2-1]=
                    _mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*2-1],
                                  LAuthBit[id*4*2*(PartyNumber-1)+2*(PartyNumber-1)+j*2+1]);
                    
                    AESPack[4*PartyNumber*id+PartyNumber*3-1]=
                    _mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*3-1],
                                  LAuthBit[id*4*2*(PartyNumber-1)+4*(PartyNumber-1)+j*2+1]);
                    AESPack[4*PartyNumber*id+PartyNumber*4-1]=
                    _mm_xor_si128(AESPack[4*PartyNumber*id+PartyNumber*4-1],
                                  LAuthBit[id*4*2*(PartyNumber-1)+6*(PartyNumber-1)+j*2+1]);
                    AESPack[4*PartyNumber*id+j]=_mm_xor_si128(AESPack[4*PartyNumber*id+j],LAuthBit[id*4*2*(PartyNumber-1)+j*2]);
                    AESPack[4*PartyNumber*id+j+PartyNumber]=_mm_xor_si128(AESPack[4*PartyNumber*id+j+PartyNumber],LAuthBit[id*4*2*(PartyNumber-1)+2*(PartyNumber-1)+j*2]);
                    AESPack[4*PartyNumber*id+j+PartyNumber*2]=_mm_xor_si128(AESPack[4*PartyNumber*id+j+PartyNumber*2],LAuthBit[id*4*2*(PartyNumber-1)+4*(PartyNumber-1)+j*2]);
                    AESPack[4*PartyNumber*id+j+PartyNumber*3]=_mm_xor_si128(AESPack[4*PartyNumber*id+j+PartyNumber*3],LAuthBit[id*4*2*(PartyNumber-1)+6*(PartyNumber-1)+j*2]);
                    
                }
                gathersrc=&(AESPack[4*PartyNumber*id]);
                Gather(IO,0,gathersrc,4*PartyNumber*16);
                id++;
            }
        }
    }
    else{
        void *gatherdst[PartyNumber];
        block hashvalue[PartyNumber];
        block bit[2];
        int id=0;
        unsigned char indicator;
        for(int i=0;i<index;i++)
        {
            if(queue[i].type==0)
            {
           //     printf("AND %d\n",i);
                for(int j=1;j<PartyNumber;j++)
                    gatherdst[j]=&(receivedgarbledrow[(j-1)*PartyNumber*4*MStageSize+id*4*PartyNumber]);
                Gather(IO,0,gatherdst,4*PartyNumber*16);
                indicator=(extract_bit(*queue[i].l->Label)<<1)^extract_bit(*queue[i].r->Label);
                indicator^=SolderRecord[id];
                unsigned char bit;
                bit=extract_bit(LAuthBit[id*4*2*(PartyNumber-1)+indicator*(PartyNumber-1)*2]);
                for(int j=0;j<PartyNumber-1;j++)
                {
                    queue[i].o->Label[j]=LAuthBit[id*4*2*(PartyNumber-1)+indicator*2*(PartyNumber-1)+j*2];
                }
                for(int j=0;j<PartyNumber-1;j++)
                {
                    hash(hashvalue,_mm_and_si128(queue[i].l->Label[j],MP->bed1),_mm_and_si128(queue[i].r->Label[j],MP->bed1),i,&Public_AES_KEY);
                    for(int k=0;k<PartyNumber;k++)
                        hashvalue[k]=_mm_xor_si128(hashvalue[k],receivedgarbledrow[j*PartyNumber*4*MStageSize+id*4*PartyNumber+indicator*PartyNumber+k]);
                    if(MP->CheckBit(hashvalue[0],LAuthBit[id*4*2*(PartyNumber-1)+indicator*(PartyNumber-1)*2+j*2+1])!=true)
                    {
                        printf("Eval check error %d %d %d\n",id,j+1,indicator);
                        print(hashvalue[0]);
                        print(receivedgarbledrow[j*PartyNumber*4*MStageSize+id*4*PartyNumber+indicator*PartyNumber]);
                        print(LAuthBit[id*4*2*(PartyNumber-1)+indicator*(PartyNumber-1)*2+j*2+1]);
                        exit(0);
                    }
                    queue[i].o->Label[j]=_mm_xor_si128(queue[i].o->Label[j],hashvalue[PartyNumber-1]);
                    for(int k=0;k<j;k++)
                    {
                        queue[i].o->Label[k]=_mm_xor_si128(queue[i].o->Label[k],hashvalue[k+1]);
                    }
                    for(int k=j+1;k<PartyNumber-1;k++)
                    {
                        queue[i].o->Label[k]=_mm_xor_si128(queue[i].o->Label[k],hashvalue[k]);
                    }
                    bit^=extract_bit(hashvalue[0]);
                }
                queue[i].o->Label[0]=_mm_and_si128(queue[i].o->Label[0],MP->bed1);
                if(bit==1)
                    queue[i].o->Label[0]=_mm_xor_si128(queue[i].o->Label[0],MP->plainbit1);
                id++;
            }
            else
            {
                if(queue[i].type==1)
                {
               //     printf("XOR %d\n",i);
                    for(int j=0;j<PartyNumber-1;j++)
                        queue[i].o->Label[j]=_mm_xor_si128(queue[i].l->Label[j],queue[i].r->Label[j]);
                }
                else
                {
                 //   printf("COPY %d\n",i);
                    for(int j=0;j<PartyNumber-1;j++)
                        queue[i].o->Label[j]=queue[i].l->Label[j];
                }
            }
        }
    }
}
void MStage::ReleaseRecord(Index i)
{
    release_record[release_index]=i;
    release_index++;
    if(release_index>=MStageSize*blowup)
    {
        exec();
        reset();
        //error("Too Many Release\n");
    }
}
void MStage::ReleaseAll()
{
    for(int i=0;i<release_index;i++)
    {
        StageMap->release(release_record[i]);
    }
    release_index=0;
}
