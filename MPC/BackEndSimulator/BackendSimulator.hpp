//
//  BackendSimulator.hpp
//  
//
//  Created by Sourgroup on 4/2/18.
//

#ifndef BackendSimulator_hpp
#define BackendSimulator_hpp

#include <stdio.h>
#include <stdlib.h>
static const int PN=1;
typedef int Index;
typedef Index bit;
typedef struct{
    unsigned char value;
    uint64_t temp[3*2*(PN-1)];
    bool valid;
}Wire;
class wiremap
{
private:
    Wire *wirebed;
    Index *nextid;
    int size;
    int idindex;
    int minium;
public:
        int InputCount;
    void Setup(int mapsize)
    {
        InputCount=0;
        size=mapsize;
        wirebed=(Wire*)malloc(sizeof(Wire)*size);
        nextid=(Index*)malloc(sizeof(Index)*size);
        for(int i=0;i<size;i++)
        {
            wirebed[i].value=0;
            wirebed[i].valid=false;
            nextid[i]=i;
        }
        idindex=size;
        minium=size;
    }
    Index New()
    {
        if(idindex<1)
        {
            printf("Out of memory!\n");
            exit(0);
        }
        idindex--;
        if(idindex<minium)
            minium=idindex;
        wirebed[nextid[idindex]].valid=true;
        return nextid[idindex];
    }
    Wire *Read(Index id)
    {
        if((id<0)||(id>size))
        {
            printf("Invalid wire id when read: %d\n",id);
            exit(0);
        }
        if(wirebed[id].valid==false)
        {
            printf("Read from uninitialized memory. Wire id: %d\n",id);
        }
        return &(wirebed[id]);
    }
    void Release(Index id)
    {
        if(id==-1)
            return;
        if((id<0)||(id>size))
        {
            printf("Invalid wire when release: %d\n",id);
            exit(0);
        }
        if(wirebed[id].valid==false)
        {
            printf("Release uninitialized memory. Wire id: %d\n",id);
        }
        nextid[idindex]=id;
        wirebed[id].valid=false;
        idindex++;
    }
    void Scan()
    {
        printf("peak=%d\n",size-minium);
        if(idindex>=size)
        {
            printf("All memory are released.\n");
            return;
        }
        else
        {
            printf("There are %d occupied slots. There were %d inputs\n",size-idindex,InputCount);
            if(size-idindex-InputCount>0)
                printf("There might be leakage of %d bits\n",size-idindex-InputCount);
            /*
            for(int i=idindex;i<size;i++)
            {
                printf("Wire %d is used\n",nextid[i]);
            }
             */
        }
    }
};
extern wiremap Map;
inline Index __pool__XOR(Index x, Index y)
{
    extern long long XORCount;
    XORCount++;
   // printf("XOR %d %d\n",x,y);
    Index z;
    z=Map.New();
    Map.Read(z)->value=(Map.Read(x)->value)^(Map.Read(y)->value);
    for(int i=0;i<6*(PN-1);i++)
        Map.Read(z)->temp[i]=Map.Read(x)->temp[i]^Map.Read(y)->temp[i];
    return z;
}
inline Index __pool__AND(Index x, Index y)
{
    extern long long ANDCount;
    ANDCount++;
   // printf("AND %d %d\n",x,y);
    Index z;
    z=Map.New();
    Map.Read(z)->value=(Map.Read(x)->value)&(Map.Read(y)->value);
    for(int i=0;i<6*(PN-1);i++)
        Map.Read(z)->temp[i]=Map.Read(x)->temp[i]&Map.Read(y)->temp[i];
    return z;
}
inline Index __pool__COPY(Index x)
{
//    printf("COPY %d\n",x);
    Index z;
    z=Map.New();
    Map.Read(z)->value=(Map.Read(x)->value);
    for(int i=0;i<6*(PN-1);i++)
        Map.Read(z)->temp[i]=Map.Read(x)->temp[i];
    return z;
}
inline void __pool__RELEASE(Index x)
{
    if(x!=-1)
        Map.Release(x);
}
inline Index __pool__NOT(Index x)
{
    Index z;
    z=__pool__COPY(x);
    Map.Read(z)->value=1^(Map.Read(x)->value);
    return z;
}inline Index __pool__OR(Index x, Index y)
{
    Index nx,ny,nz,z;
    nx=__pool__NOT(x);
    ny=__pool__NOT(y);
    nz=__pool__AND(nx,ny);
    z=__pool__NOT(nz);
    __pool__RELEASE(nx);
    __pool__RELEASE(ny);
    __pool__RELEASE(nz);
    return z;
}
inline Index Input()
{
    Map.InputCount++;
    Index z=Map.New();
    Map.Read(z)->value=0;
    for(int i=0;i<6*(PN-1);i++)
        Map.Read(z)->temp[i]=0;

    return z;
}
inline Index Input(unsigned char value)
{
    Map.InputCount++;
    Index z=Map.New();
    Map.Read(z)->value=value;
    for(int i=0;i<6*(PN-1);i++)
        Map.Read(z)->temp[i]=0;

    return z;
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

inline void CheckLeakage()
{
    Map.Scan();
}
inline Index XOR(Index x, Index y)
{
    extern long long XORCount;
    XORCount++;
//      printf("XOR %d %d\n",x,y);
    Index z;
    z=Map.New();
    Map.Read(z)->value=(Map.Read(x)->value)^(Map.Read(y)->value);
    for(int i=0;i<6*(PN-1);i++)
        Map.Read(z)->temp[i]=Map.Read(x)->temp[i]^Map.Read(y)->temp[i];

    return z;
}
inline Index AND(Index x, Index y)
{
    extern long long ANDCount;
    ANDCount++;
//      printf("AND %d %d\n",x,y);
    Index z;
    z=Map.New();
    Map.Read(z)->value=(Map.Read(x)->value)*(Map.Read(y)->value);
    for(int i=0;i<6*(PN-1);i++)
        Map.Read(z)->temp[i]=Map.Read(x)->temp[i]&Map.Read(y)->temp[i];
    return z;
}
inline Index NOT(Index x)
{
    Index z;
    z=__pool__COPY(x);
    Map.Read(z)->value=1^(Map.Read(x)->value);
    for(int i=0;i<6*(PN-1);i++)
        Map.Read(z)->temp[i]=Map.Read(x)->temp[i];

    return z;
}inline Index OR(Index x, Index y)
{
    Index nx,ny,nz,z;
    nx=__pool__NOT(x);
    ny=__pool__NOT(y);
    nz=__pool__AND(nx,ny);
    z=__pool__NOT(nz);
    __pool__RELEASE(nx);
    __pool__RELEASE(ny);
    __pool__RELEASE(nz);
    return z;
}
#endif /* BackendSimulator_hpp */
