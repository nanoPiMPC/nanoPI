//
//  Stage.hpp
//  
//
//  Created by Sourgroup on 11/17/17.
//

#ifndef Stage_hpp
#define Stage_hpp
#define blowup 10
#include <stdio.h>
#include "Wiremap.hpp"
#include "Pool.hpp"
typedef struct{
    unsigned char type;
    wire *o;
    wire *l,*r;
}Gate_Record;
class MStage{
private:
    int MyID;
    uint64_t AndSum;
    uint32_t index;
    uint32_t release_index;
    uint32_t MStageSize;
    Network *IO;
    unsigned char* SolderRecord;
    Index *release_record;
    Gate_Record* queue;
    block *OAuthBit;
    block *Tuples;
    block *LAuthBit;
    block *Label0;
    block *AESPack;
    block *SolderingProveBuffer;
    block *SolderingVerifyBuffer;
    block *rcoe;
    block *receivedgarbledrow;
    AES_KEY Public_AES_KEY;
    uint64_t Public_Count;
    void andeval(wire *o,wire *l, wire *r,int index);
    void ReleaseAll();
    void exec();
    void reset();
    void Solder();
    void Garbling();
    void Eval();
public:
    int XORCount,ANDCount;
    MPool *MP;
    wiremap *StageMap;
    void ReleaseRecord(Index i);
    void Setup(int id,uint32_t MStgSize,MPool *P,wiremap *M);
    void andpre(wire *o, wire *l, wire *r);
    void xorpre(wire *o, wire *l, wire *r);
    void copypre(wire *o,wire *l);
    void Close();
    void PrintCount()
    {
        printf("AND %d\nXOR %d\n",ANDCount,XORCount);
        IO->PrintCount();
    }
};
extern MStage S;

extern wiremap Map;
inline Index __pool__XOR(Index x, Index y);
inline Index __pool__AND(Index x, Index y);
inline Index __pool__COPY(wire *w);
inline wire * READ(Index i);
inline void __pool__RELEASE(Index i);
inline Index __pool__XOR(Index x, Index y)
{
    Index i = S.StageMap->New();
    wire* z = S.StageMap->Read(i);
    S.xorpre(z,S.StageMap->Read(x),S.StageMap->Read(y));
    return i;
}
inline Index __pool__AND(Index x, Index y)
{
    Index i = S.StageMap->New();
    wire* z = S.StageMap->Read(i);
    S.andpre(z,S.StageMap->Read(x),S.StageMap->Read(y));
    return i;

}
inline Index __pool__COPY(Index x)
{
    Index i = S.StageMap->New();
    wire* z = S.StageMap->Read(i);
    S.copypre(z,S.StageMap->Read(x));
    return i;
    
}
inline Index __pool__NOT(Index x)
{
    extern Index One;
    return __pool__XOR(x,One);
}
inline void __pool__RELEASE(Index i)
{
    if(i!=-1)
        S.ReleaseRecord(i);
}
inline Index __pool__OR(Index x, Index y)
{
    Index a = __pool__NOT(x);
    Index b = __pool__NOT(y);
    Index c = __pool__AND(a,b);
    Index o = __pool__NOT(c);
    __pool__RELEASE(a);
    __pool__RELEASE(b);
    __pool__RELEASE(c);
    return o;
}
inline Index __pool__Input(int id,unsigned char c)
{
    Index i = S.StageMap->New();
    S.MP->BatchInput(S.StageMap->Read(i),id,c);
    return i;
    
}
inline void __pool_InputFlush()
{
    S.MP->BatchInputFlush();
}
inline Index __pool__NewVar()
{
    return -1;
}
inline void __pool__NewArray(Index array[],int size)
{
    for(int i=0;i<size;i++)
        array[i]=__pool__NewVar();
}
inline void __pool__RELEASEArray(Index array[],int size)
{
    for(int i=0;i<size;i++)
        __pool__RELEASE(array[i]);
}
#endif /* Stage_hpp */
