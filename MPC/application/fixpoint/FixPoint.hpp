//
//  FixPoint.hpp
//  
//
//  Created by Sourgroup on 4/27/18.
//

#ifndef FixPoint_hpp
#define FixPoint_hpp
#ifdef Plaintext
#include "PlaintextSimulator.hpp"
#else
#ifdef Simulator
#include "BackendSimulator.hpp"
#else
#include "Stage.hpp"
#endif
#endif
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
extern Index Zero,One;
#define Lfix 24
#define Lpoint 12
#define max (1<<(Lfix-Lpoint))
#define Max (1<<Lfix)
typedef struct{
    Index bits[Lfix];
}__pool__fixpoint;
typedef struct{
    Index bit;
}__pool__bool;
inline void __pool__init__bool(__pool__bool *dst)
{
    dst->bit=__pool__NewVar();
}
inline void __pool__make__bool(__pool__bool *dst,bool v)
{
    if(v)
    {
#ifdef Simulator
        dst->bit=Input(1);
#else
        dst->bit=__pool__COPY(One);
#endif
    }
    else
    {
#ifdef Simulator
        dst->bit=Input(0);
#else
        dst->bit=__pool__COPY(Zero);
#endif
    }
}
inline void __pool__RELEASE__bool(__pool__bool *dst)
{
    __pool__RELEASE(dst->bit);
}
inline void __pool__init__fixpoint(__pool__fixpoint *dst)
{
    for(int i=0;i<Lfix;i++)
        dst->bits[i]=__pool__NewVar();
}
inline void __pool__make__fixpoint(__pool__fixpoint *dst,double value)
{
    if(abs(value)>max)
    {
        printf("Value too large %lf\n",value);
        exit(0);
    }
    __pool__init__fixpoint(dst);
   unsigned long long tmp=abs(value)*(1<<Lpoint);
    printf("%llu\n",tmp);
    if(value<0)
    {
        tmp=Max-tmp;
    }
    for(int i=0;i<Lfix;i++)
    {
        if((tmp&0x1)==0)
        {
#ifdef Simulator
            dst->bits[i]=Input(0);
#else
            dst->bits[i]=__pool__COPY(Zero);
#endif
        }
        else
        {
#ifdef Simulator
            dst->bits[i]=Input(1);
#else
            dst->bits[i]=__pool__COPY(One);
#endif
        }
        tmp=tmp>>1;
    }
}
inline void __pool__RELEASE__fixpoint(__pool__fixpoint *dst)
{
    for(int i=0;i<Lfix;i++)
    {
        __pool__RELEASE(dst->bits[i]);
        dst->bits[i]=__pool__NewVar();
    }
}
inline void __pool__COPY__fixpoint(__pool__fixpoint *dst,__pool__fixpoint *src)
{
    __pool__RELEASE__fixpoint(dst);
    for(int i=0;i<Lfix;i++)
        dst->bits[i]=__pool__COPY(src->bits[i]);
}
void __pool__fixpoint__mux(__pool__fixpoint *dst,__pool__fixpoint *op1, __pool__fixpoint *op2, __pool__bool *c);
void __pool__fixpoint__add(__pool__fixpoint *dst,__pool__fixpoint *op1, __pool__fixpoint *op2);
void __pool__fixpoint__sub(__pool__fixpoint *dst,__pool__fixpoint *op1, __pool__fixpoint *op2);
void __pool__fixpoint__mul(__pool__fixpoint *dst,__pool__fixpoint *op1, __pool__fixpoint *op2);
void __pool__fixpoint__lt(__pool__bool *dst,__pool__fixpoint *op1, __pool__fixpoint *op2);
#ifdef Simulator
inline double reveal(__pool__fixpoint *dst)
{
   unsigned long long tmp=0;
    for(int i=Lfix-1;i>0;i--)
    {
        tmp=tmp+Map.Read(dst->bits[i])->value;
        tmp=tmp<<1;
    }
    tmp=tmp+Map.Read(dst->bits[0])->value;
    double result=tmp*1.0/(1<<Lpoint);
    if(Map.Read(dst->bits[Lfix-1])->value==1)
        result=result-max;
    printf("%llu \n",tmp);
    return result;
}
#endif

#endif /* FixPoint_hpp */
