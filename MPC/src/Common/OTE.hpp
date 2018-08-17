//
//  OTE.hpp
//  
//
//  Created by Sourgroup on 12/13/17.
//

#ifndef OTE_hpp
#define OTE_hpp
#include "PRG.hpp"
#include "Network_IO.hpp"
#include <openssl/sha.h>
class OTSet{
public:
    void Setup(int myid,int partnerid,block D,int size,block seed,Network *IO);
    void BiOT(block *dst,int n);
    void OTClose();
    void OTExtension(block *dst);
    block MatrixI[168];
    block MatrixR[168];
    unsigned char hash[SHA256_DIGEST_LENGTH*3];
    block seed,seedR;
    block tmp[2],t[2],tt[2],x,X;
    block *OTBuffer;
    block *OTEtemp;
    Network *IO;
    int MyID,PartnerID;
    int size;
    void OTExtension1(block *dst);
    void OTExtension2(block *dst);
    void OTExtension3(block *dst);
    void OTExtension4(block *dst);
    void DeltaConsistencyCheck1();
    void DeltaConsistencyCheck2();
    void DeltaConsistencyCheck3();
    void ConsistencyCheck1();
    void ConsistencyCheck2();
    void ConsistencyCheck3();
    void exchange(void *dst,void *src,int size);
    void exchange(void *dst1,void *dst2,void *src1,void *src2,int size1,int size2);
private:
    block tmp1,tmp2,q[2];
    block t0;
    block tmpd[256];
    AES_KEY LKey,RKey;
    int OTBufferSize;
    int LabelBufferSize;
    const block All1=_mm_set_epi32(0xffffffff,0xffffffff,0xffffffff,0xffffffff);
    const block DeltaCheckBlock=_mm_set_epi8(0,0,0,0,0,0xff,0xff,0xff,0xff,0xff,0,0,0,0,0,0);
    const block bed1=_mm_set_epi32(0xffffffff,0xffffffff,0xffffffff,0xfffffffe);
    int LabelBufferIndex;
    int OTBufferIndex=0;
    AES_KEY Private_AES_KEY,Public_AES_KEY;
    block Delta;
    block RandomSeed;
    uint64_t Public_Count,Private_Count;
    unsigned char BaseOTChoice[168];
    block MatrixINext[168];
    block MatrixDelta[128];
    block ChoiceZero[168];
    block BaseOTTemp[512];
    block CCheckIndex[41];
    block GDelta[2];
    block BaseOTSend[168][2];
    block BaseOTRec[168];
    block DeltaCheck[80];
    block PreTable[256*21];
    block PreTableR[256*21];
    block DeltaCheckChoice=_mm_set_epi32(0,0,0,0);
    block *OTEChoice,*LabelBuffer,*index,*ChiThis,*ChiThat;
    void MatrixISetup();
    void GarbleMatrix();
    void PreTableGene();
    void BatchMulti_1(block *dst, block *src);
    void BatchMulti_2(block *dst, block *src);
    void ExtractChoiceZero();
    void ExtractBaseOT();
    void ConsistencyCheck();
    void DeltaConsistencyCheck();
    void NewLabels(block *dst, int n);
    void RefreshLabel(block *dst, int n);
};
extern OTSet OTS;
#endif /* OTE_hpp */
