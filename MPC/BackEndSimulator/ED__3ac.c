#ifdef Plaintext
#include "PlaintextSimulator.hpp"
#else
#ifndef Simulator
#include "Stage.hpp"
#else
#include "BackendSimulator.hpp"
#endif
#endif
extern Index Zero,One;
#define Length 11
#define EDLength 2000
Index Mux1(Index x, Index y, Index c)
{
    Index __tmp__5 = __pool__XOR(x, y);
    Index __tmp__4 = __pool__XOR(c, __tmp__5);
    Index __tmp__3 = __pool__AND(x, __tmp__4);
    __pool__RELEASE(__tmp__4);
    __pool__RELEASE(__tmp__5);
    return __tmp__3;
}

void Mux(Index *z, Index *x, Index *y, Index c)
{
    int i;
    for (i = 0; i < Length; i++)
        z[i] = Mux1(x[i], y[i], c);
}

Index Compare1(Index x, Index y, Index c)
{
    Index __tmp__9 = __pool__XOR(x, y);
    Index __tmp__8 = Mux1(c, x, __tmp__9);
    __pool__RELEASE(__tmp__9);
    return __tmp__8;
}

Index Compare(Index *x, Index *y)
{
    
    Index __tmp__12 = __pool__XOR(x[0], y[0]);
    Index t = __pool__AND(__tmp__12, x[0]);
    __pool__RELEASE(__tmp__12);
    for (int i = 1; i < Length; i++)
    {
        Index tmp = Compare1(x[i], y[i], t);
        __pool__RELEASE(t);
        t=tmp;
    }
    return t;
}

void add(Index *z, Index *x, Index *y)
{
    Index t = __pool__AND(x[0], y[0]);
    z[0] = __pool__XOR(x[0], y[0]);
    int i;
    for (i = 1; i < Length; i++)
    {
        Index __tmp__20 = __pool__XOR(t, x[i]);
        Index __tmp__21 = Mux1(x[i], y[i], __tmp__20);
        __pool__RELEASE(z[i]);
        z[i]=__tmp__20;
        __pool__RELEASE(t);
        t = __tmp__21;
        Index __tmp__22 = __pool__XOR(z[i], y[i]);
        __pool__RELEASE(z[i]);
        z[i] = __tmp__22;
    }
    __pool__RELEASE(t);
}

void add1(Index *z, Index *x, Index y)
{
    Index t = __pool__AND(x[0], y);
    z[0] = __pool__XOR(x[0], y);


    int i;
    for (i = 1; i < Length; i++)
    {
        Index __tmp__20 = __pool__XOR(t, x[i]);
        __pool__RELEASE(z[i]);
        z[i]=__tmp__20;
        Index __tmp__21 = Mux1(x[i],Zero , __tmp__20);
        __pool__RELEASE(t);
        t = __tmp__21;
    }
    
    __pool__RELEASE(t);
}

void ED(Index *z, Index *x, Index *y)
{
    Index matrix0[(EDLength+1)*Length];
    Index matrix1[(EDLength+1)*Length];
    Index a[4*Length];
    int i,j;

    for(int i=0;i<(EDLength+1)*Length;i++)
    {
        matrix0[i]=__pool__NewVar();
        matrix1[i]=__pool__NewVar();
    }
    for(i=0;i<4*Length;i++)
        a[i]=__pool__NewVar();
    for(i=0;i<Length;i++)
    {
        matrix0[i]=__pool__COPY(Zero);
    }
    for(i=1;i<EDLength+1;i++)
    {
        add1(&(matrix0[i*Length]),&(matrix0[(i-1)*Length]),One);
    }
    for(i=1;i<EDLength+1;i++)
    {
        printf("i=%d\n",i);
        add1(matrix1,matrix0,One);
        for(j=1;j<EDLength+1;j++)
        {
            add1(a,&(matrix0[j*Length]),One);
            add1(&(a[Length]),&(matrix1[(j-1)*Length]),One);
            Index tmp1=__pool__XOR(x[2*(i-1)],y[2*(j-1)]);
            Index tmp2=__pool__XOR(x[2*(i-1)+1],y[2*(j-1)+1]);
            Index tmp3=__pool__AND(tmp1,tmp2);

            add1(&(a[2*Length]),&(matrix0[(j-1)*Length]),tmp3);
            Index tmp4=Compare(a,&(a[1*Length]));
            Mux(&(a[3*Length]),a,&(a[1*Length]),tmp4);
            Index tmp5=Compare(&(a[3*Length]),&(a[2*Length]));
            Mux(&(matrix1[j*Length]),&(a[3*Length]),&(a[2*Length]),tmp5);
            __pool__RELEASE(tmp1);
            __pool__RELEASE(tmp2);
            __pool__RELEASE(tmp3);
            __pool__RELEASE(tmp4);
            __pool__RELEASE(tmp5);
            for(int k=0;k<Length;k++)
            {
                __pool__RELEASE(matrix0[(j-1)*Length+k]);
                matrix0[(j-1)*Length+k]=matrix1[(j-1)*Length+k];
                matrix1[(j-1)*Length+k]=__pool__NewVar();
            }
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<Length;j++)
                {
                    __pool__RELEASE(a[i*Length+j]);
                    a[i*Length+j]=__pool__NewVar();
                }
            }
        }
        for(int k=0;k<Length;k++)
        {
            __pool__RELEASE(matrix0[EDLength*Length+k]);
            matrix0[EDLength*Length+k]=matrix1[EDLength*Length+k];
            matrix1[EDLength*Length+k]=__pool__NewVar();
        }
    }
    
    for(i=0;i<Length;i++)
        z[i]=__pool__COPY(matrix0[EDLength+i]);
    
    for(int j=0;j<Length*(EDLength+1);j++)
        {
            __pool__RELEASE(matrix0[i]);
        }
}
#ifndef Simulator
#ifndef Plaintext
void Application()
{
    Zero=S.StageMap->Zero;
    One=S.StageMap->One;
    auto t0=clock_start();
    Index array[EDLength*4];
    for(int i=0;i<EDLength*4;i++)
    {
        array[i]=__pool__NewVar();
        array[i]=S.StageMap->New();
        MP.BatchInput(S.StageMap->Read(array[i]),0,1-i%2);
    }
    MP.BatchInputFlush();
    Index result[Length];
    for(int i=0;i<Length;i++)
        result[i]=__pool__NewVar();
    printf("IO cost: %lf s\n",time_from(t0)/1000000);
#ifdef IOTimer
    extern uint64_t MOTE_BWCounter,Stage_BWCounter,Tuples_BWCounter;
    extern int MOTE_Counter;
    printf("MOTE: %d %lld  Stage: %lld Tuple: %lld\n",MOTE_Counter,MOTE_BWCounter,Stage_BWCounter,Tuples_BWCounter);
#endif
    IO.PrintCount();
    t0=clock_start();
    ED(result,array,&(array[EDLength*2]));
    double t1=time_from(t0);
    printf("Time=%lf\n",t1/1000000);
    S.Close();
    S.PrintCount();
#ifdef IOTimer
    extern uint64_t MOTE_BWCounter,Stage_BWCounter,Tuples_BWCounter;
    extern int MOTE_Counter,Stage_BitCounter;
    printf("MOTE: %d %lld  Stage: %d %lld Tuple: %lld\n",MOTE_Counter,MOTE_BWCounter,Stage_BitCounter,Stage_BWCounter,Tuples_BWCounter);
#endif
}
#endif
#endif


