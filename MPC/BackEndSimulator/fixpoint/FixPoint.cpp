//
//  FixPoint.cpp
//
//
//  Created by Sourgroup on 4/27/18.
//

#include "FixPoint.hpp"
Index __pool__bit__mux(Index x,Index y, Index c)
{
    Index tmp1=__pool__NewVar();
    Index tmp2=__pool__NewVar();
    Index tmp3=__pool__NewVar();
    tmp1=__pool__XOR(x,y);
    tmp2=__pool__AND(tmp1,c);
    tmp3=__pool__XOR(tmp2,x);
    __pool__RELEASE(tmp1);
    __pool__RELEASE(tmp2);
    return tmp3;
}
void __pool__fixpoint__mux(__pool__fixpoint *dst,__pool__fixpoint *op1, __pool__fixpoint *op2, __pool__bool *c)
{
    __pool__RELEASE__fixpoint(dst);
    for(int i=0;i<Lfix;i++)
    {
        dst->bits[i]=__pool__bit__mux(op1->bits[i],op2->bits[i],c->bit);
    }
}
void __pool__fixpoint__add(__pool__fixpoint *dst,__pool__fixpoint *op1, __pool__fixpoint *op2)
{
    __pool__RELEASE__fixpoint(dst);
    Index d=__pool__NewVar();
    Index tmp1=__pool__NewVar();
    Index tmp2=__pool__NewVar();
    __pool__RELEASE(d);
    d=__pool__AND(op1->bits[0],op2->bits[0]);
    dst->bits[0]=__pool__XOR(op1->bits[0],op2->bits[0]);
    
    for(int i=1;i<Lfix-1;i++)
    {
        __pool__RELEASE(tmp1);
        tmp1=__pool__XOR(op1->bits[i],op2->bits[i]);
        dst->bits[i]=__pool__XOR(d,tmp1);
        __pool__RELEASE(tmp2);
        tmp2=__pool__bit__mux(op1->bits[i],d,tmp1);
        __pool__RELEASE(d);
        d=__pool__COPY(tmp2);
    }
    {
        int i=Lfix-1;
        __pool__RELEASE(tmp1);
        tmp1=__pool__XOR(op1->bits[i],op2->bits[i]);
        dst->bits[i]=__pool__XOR(d,tmp1);
        __pool__RELEASE(tmp1);
        __pool__RELEASE(tmp2);
        __pool__RELEASE(d);
    }
}
void __pool__fixpoint__sub(__pool__fixpoint *dst,__pool__fixpoint *op1, __pool__fixpoint *op2)
{
    __pool__RELEASE__fixpoint(dst);
    Index d=__pool__NewVar();
    Index tmp1=__pool__NewVar();
    Index tmp2=__pool__NewVar();
    __pool__RELEASE(d);
    d=__pool__AND(op1->bits[0],op2->bits[0]);
    dst->bits[0]=__pool__XOR(op1->bits[0],op2->bits[0]);
    
    for(int i=1;i<Lfix-1;i++)
    {
        __pool__RELEASE(tmp1);
        tmp1=__pool__XOR(op1->bits[i],op2->bits[i]);
        dst->bits[i]=__pool__XOR(d,tmp1);
        __pool__RELEASE(tmp2);
        tmp2=__pool__bit__mux(d,op2->bits[i],tmp1);
        __pool__RELEASE(d);
        d=__pool__COPY(tmp2);
    }
    {
        int i=Lfix-1;
        __pool__RELEASE(tmp1);
        tmp1=__pool__XOR(op1->bits[i],op2->bits[i]);
        dst->bits[i]=__pool__XOR(d,tmp1);
        __pool__RELEASE(tmp1);
        __pool__RELEASE(tmp2);
        __pool__RELEASE(d);
    }
}
void __pool__fixpoint__mul(__pool__fixpoint *dst,__pool__fixpoint *op1, __pool__fixpoint *op2)
{
    __pool__RELEASE__fixpoint(dst);
    Index tmp[Lfix+Lpoint];
    Index tmpv=__pool__NewVar();
    Index tmpr=__pool__NewVar();
    Index d=__pool__NewVar();
    Index tmp1=__pool__NewVar();
    Index tmp2=__pool__NewVar();
    //first add num
    for(int i=0;i<Lfix;i++)
    {
        tmp[i]=__pool__AND(op1->bits[i],op2->bits[0]);
    }
    for(int i=Lfix;i<Lfix+Lpoint;i++)
        tmp[i]=__pool__NewVar();
    
    tmp[Lfix]=__pool__COPY(Zero);
    //2nd to Lpoint-1 add
    for(int shift=1;shift<Lpoint;shift++)
    {
        __pool__RELEASE(tmpv);
        tmpv=__pool__AND(op1->bits[0],op2->bits[shift]);
        __pool__RELEASE(d);
        d=__pool__AND(tmp[shift],tmpv);
        __pool__RELEASE(tmpr);
        tmpr=__pool__XOR(tmp[shift],tmpv);
        __pool__RELEASE(tmp[shift]);
        tmp[shift]=tmpr;
        tmpr=-1;
        for(int i=1;i<Lfix-1;i++)
        {
            __pool__RELEASE(tmpv);
            tmpv=__pool__AND(op1->bits[i],op2->bits[shift]);
            __pool__RELEASE(tmp1);
            tmp1=__pool__XOR(tmpv,tmp[shift+i]);
            __pool__RELEASE(tmpr);
            tmpr=__pool__XOR(tmp1,d);
            __pool__RELEASE(tmp2);
            tmp2=__pool__bit__mux(tmpv,d,tmp1);
            __pool__RELEASE(d);
            d=tmp2;
            tmp2=-1;
            __pool__RELEASE(tmp[shift+i]);
            tmp[shift+i]=tmpr;
            tmpr=-1;
        }
        
        {
            int i=Lfix-1;
            __pool__RELEASE(tmpv);
            tmpv=__pool__AND(op1->bits[i],op2->bits[shift]);
            __pool__RELEASE(tmp1);
            tmp1=__pool__XOR(tmpv,tmp[shift+i]);
            __pool__RELEASE(tmpr);
            tmpr=__pool__XOR(tmp1,d);
            __pool__RELEASE(tmp2);
            tmp2=__pool__bit__mux(tmpv,d,tmp1);
            __pool__RELEASE(tmp[shift+i+1]);
            tmp[shift+i+1]=tmp2;
            tmp2=-1;
            __pool__RELEASE(tmp[shift+i]);
            tmp[shift+i]=tmpr;
            tmpr=-1;
        }
    }
//Lpoint add
    {
        int shift=Lpoint;
        __pool__RELEASE(tmpv);
        tmpv=__pool__AND(op1->bits[0],op2->bits[shift]);
        __pool__RELEASE(d);
        d=__pool__AND(tmp[shift],tmpv);
        __pool__RELEASE(tmpr);
        tmpr=__pool__XOR(tmp[shift],tmpv);
        __pool__RELEASE(tmp[shift]);
        tmp[shift]=tmpr;
        tmpr=-1;
        for(int i=1;i<Lfix-1;i++)
        {
            __pool__RELEASE(tmpv);
            tmpv=__pool__AND(op1->bits[i],op2->bits[shift]);
            __pool__RELEASE(tmp1);
            tmp1=__pool__XOR(tmpv,tmp[shift+i]);
            __pool__RELEASE(tmpr);
            tmpr=__pool__XOR(tmp1,d);
            __pool__RELEASE(tmp2);
            tmp2=__pool__bit__mux(tmpv,d,tmp1);
            __pool__RELEASE(d);
            d=tmp2;
            tmp2=-1;
            __pool__RELEASE(tmp[shift+i]);
            tmp[shift+i]=tmpr;
            tmpr=-1;
        }
        int i=Lfix-1;
        __pool__RELEASE(tmpv);
        tmpv=__pool__AND(op1->bits[i],op2->bits[shift]);
        __pool__RELEASE(tmp1);
        tmp1=__pool__XOR(tmpv,tmp[shift+i]);
        __pool__RELEASE(tmpr);
        tmpr=__pool__XOR(tmp1,d);
        __pool__RELEASE(tmp[shift+i]);
        tmp[shift+i]=tmpr;
        tmpr=-1;
    }
//Lpoint+1 to Lfix add
    for(int shift=Lpoint+1;shift<Lfix;shift++)
    {
        __pool__RELEASE(tmpv);
        tmpv=__pool__AND(op1->bits[0],op2->bits[shift]);
        __pool__RELEASE(d);
        d=__pool__AND(tmp[shift],tmpv);
        __pool__RELEASE(tmpr);
        tmpr=__pool__XOR(tmp[shift],tmpv);
        __pool__RELEASE(tmp[shift]);
        tmp[shift]=tmpr;
        tmpr=-1;
        for(int i=1;i<Lfix-1-(shift-Lpoint);i++)
        {
            __pool__RELEASE(tmpv);
            tmpv=__pool__AND(op1->bits[i],op2->bits[shift]);
            __pool__RELEASE(tmp1);
            tmp1=__pool__XOR(tmpv,tmp[shift+i]);
            __pool__RELEASE(tmpr);
            tmpr=__pool__XOR(tmp1,d);
            __pool__RELEASE(tmp2);
            tmp2=__pool__bit__mux(tmpv,d,tmp1);
            __pool__RELEASE(d);
            d=tmp2;
            tmp2=-1;
            __pool__RELEASE(tmp[shift+i]);
            tmp[shift+i]=tmpr;
            tmpr=-1;
        }
        {
            int i=Lfix-1-(shift-Lpoint);
            __pool__RELEASE(tmpv);
            tmpv=__pool__AND(op1->bits[i],op2->bits[shift]);
            __pool__RELEASE(tmp1);
            tmp1=__pool__XOR(tmpv,tmp[shift+i]);
            __pool__RELEASE(tmpr);
            tmpr=__pool__XOR(tmp1,d);
            __pool__RELEASE(tmp[shift+i]);
            tmp[shift+i]=tmpr;
            tmpr=-1;
        }
    }
    __pool__RELEASE(tmpv);
    __pool__RELEASE(tmp1);
    __pool__RELEASE(d);
    for(int i=0;i<Lfix;i++)
        dst->bits[i]=tmp[i+Lpoint];
    __pool__RELEASEArray(tmp,Lpoint);
}
void __pool__fixpoint__lt(__pool__bool *dst,__pool__fixpoint *op1, __pool__fixpoint *op2)
{
    Index tmp1=__pool__NewVar();
    Index tmp2=__pool__NewVar();
    Index tmpv=__pool__NewVar();
    __pool__RELEASE(tmp1);
    __pool__RELEASE(tmpv);
    tmp1=__pool__XOR(op1->bits[0],op2->bits[0]);
    tmpv=__pool__bit__mux(Zero,op1->bits[0],tmp1);
    for(int i=1;i<Lfix-1;i++)
    {
        __pool__RELEASE(tmp1);
        tmp1=__pool__XOR(op1->bits[i],op2->bits[i]);
        tmp2=__pool__bit__mux(tmpv,op2->bits[i],tmp1);
        __pool__RELEASE(tmpv);
        tmpv=tmp2;
        tmp2=-1;
    }
    int i=Lfix-1;
    __pool__RELEASE(tmp1);
    tmp1=__pool__XOR(op1->bits[i],op2->bits[i]);
    __pool__RELEASE__bool(dst);
    dst->bit=__pool__bit__mux(tmpv,op1->bits[i],tmp1);
    __pool__RELEASE(tmpv);
    __pool__RELEASE(tmp1);
}

