#ifdef Plaintext
#include "PlaintextSimulator.hpp"
#else
#ifndef Simulator
#include "Stage.hpp"
#else
#include "BackendSimulator.hpp"
#endif
#endif
#include "FixPoint.hpp"
extern Index Zero,One;
#define Dim 784
#define MaxDim 10
__pool__fixpoint Fzero,Fone,Fhalf,Ft1,Ft2;
void sigmoid(__pool__fixpoint *dst,__pool__fixpoint *v) {
    __pool__bool test1, test2;
    __pool__fixpoint tmp1, tmp2;
    __pool__fixpoint tmp;
      __pool__init__fixpoint(&tmp);
    __pool__init__bool(&test1);
    __pool__init__bool(&test2);
    __pool__fixpoint__lt(&test1, &Ft1,v);
    __pool__fixpoint__lt(&test2, &Ft2,v);
    __pool__fixpoint__mux(&tmp,&Fzero,&Fhalf,&test1);
    __pool__fixpoint__mux(dst,&tmp,&Fhalf,&test2);
    __pool__RELEASE__bool(&test1);
    __pool__RELEASE__bool(&test2);
    __pool__RELEASE__fixpoint(&tmp);

}

void hyp(__pool__fixpoint *dst,__pool__fixpoint x[], __pool__fixpoint* W) {
    __pool__fixpoint tmp,SUM,tmp1;
      __pool__init__fixpoint(&(tmp));
      __pool__init__fixpoint(&(SUM));
      __pool__init__fixpoint(&(tmp1));
    __pool__fixpoint__mul(&(tmp), &(W[1]), &(x[0]));
    __pool__fixpoint__add(&SUM, &(tmp), W);
    for(int i=1;i<Dim;i++)
    {
        __pool__fixpoint__mul(&tmp, &(W[i+1]), &(x[i]));
        __pool__RELEASE__fixpoint(&tmp1);
        __pool__fixpoint__add(&tmp1, &SUM, &(tmp));
        __pool__COPY__fixpoint(&SUM,&tmp1);

    }
    __pool__RELEASE__fixpoint(&(tmp1));
    __pool__RELEASE__fixpoint(&(tmp));
    sigmoid(dst,&SUM);
    __pool__RELEASE__fixpoint(&(SUM));
    return;
}

__pool__fixpoint* sgd(int size, __pool__fixpoint* X, __pool__fixpoint* y, __pool__fixpoint alpha, int n) {
    __pool__fixpoint* W = (__pool__fixpoint*) malloc(sizeof(__pool__fixpoint)*(Dim+1));
    for(int d=0;d<=Dim;d++)
        __pool__make__fixpoint(W+d, 0.0);
    for (int ep = 0; ep < n; ep++) {
        for (int i = 0; i < size; i++) {
            printf("ep %d i=%d\n",ep,i);
            __pool__fixpoint yhat;
              __pool__init__fixpoint(&yhat);
            hyp(&yhat,&(X[/*i*/0*Dim]), W);
            
            //dy=(yhat - y[i])
            // W[0] = W[0] - (alpha * dy);
            __pool__fixpoint dy, tmp1;
              __pool__init__fixpoint(&tmp1);
              __pool__init__fixpoint(&dy);
            __pool__fixpoint__sub(&dy, &yhat, y/*+i*/);
            __pool__fixpoint__mul(&tmp1, &alpha, &dy);
            __pool__RELEASE__fixpoint(&yhat);
            __pool__COPY__fixpoint(&yhat,W);
            __pool__fixpoint__sub(W, &yhat, &tmp1);
            __pool__RELEASE__fixpoint(&tmp1);
            __pool__RELEASE__fixpoint(&yhat);
            
            
            for(int d=1;d<=Dim;d++)
            {
                // W[d] = W[d] - (alpha * X[i,d] * dy);
                __pool__fixpoint tmp1, tmp2;
                  __pool__init__fixpoint(&tmp1);
                  __pool__init__fixpoint(&tmp2);
                __pool__fixpoint__mul(&tmp1, &alpha, &(X[/*i*/0*Dim+d-1]));
                __pool__fixpoint__mul(&tmp2, &dy, &tmp1);
                __pool__RELEASE__fixpoint(&tmp1);
                __pool__COPY__fixpoint(&tmp1,W+d);
                __pool__fixpoint__sub(W+d,&tmp1, &tmp2);
                __pool__RELEASE__fixpoint(&tmp2);
                __pool__RELEASE__fixpoint(&tmp1);
            }
            __pool__RELEASE__fixpoint(&dy);

        }
    }
    return W;
}

void Application() {
    static const int data_size = 1000;
    __pool__make__fixpoint(&Fzero,0.0);
    __pool__make__fixpoint(&Fone,1.0);
    __pool__make__fixpoint(&Fhalf,0.5);
    
    __pool__make__fixpoint(&Ft1,0.5);
    __pool__make__fixpoint(&Ft2,-0.5);
    
    
    
    __pool__fixpoint* X1 = (__pool__fixpoint*) malloc(sizeof(__pool__fixpoint)*/*data_size*/1*Dim);
    float X1_data[MaxDim] = {2.7810836, 1.465489372, 3.396561688,
        1.38807019, 3.06407232, 7.627531214,
        5.332441248, 6.922596716, 8.675418651,
        7.673756466};
    for (int i = 0; i < Dim; i++)
        __pool__make__fixpoint(X1+i, X1_data[i%10]);
    
    /*
    __pool__fixpoint* X2=X1;
    for(int i=1;i<data_size;i++)
    {
        X2 = X2+Dim;
        float X2_data[data_size] = {2.550537003, 2.362125076, 4.400293529,
            1.850220317, 3.005305973, 2.759262235,
            2.088626775, 1.77106367, -0.242068655,
            3.508563011};
        for (int i = 0; i < Dim; i++)
            __pool__make__fixpoint(X2+i, X2_data[i%10]);
    }
     */
    __pool__fixpoint* y = (__pool__fixpoint*) malloc(sizeof(__pool__fixpoint)*data_size);
    float y_data[data_size] = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    for (int i = 0; i < 1/*data_size*/; i++)
        __pool__make__fixpoint(y+i, y_data[i%10]);
    
    
    
    int iterations = 2;
    __pool__fixpoint alpha;
    __pool__make__fixpoint(&alpha, 1);
#ifndef Simulator
#ifndef Plaintext
        __pool_InputFlush();
    auto t0=clock_start();
#endif
#endif
    __pool__fixpoint* W = sgd(data_size, X1, y, alpha, iterations);
#ifndef Simulator
#ifndef Plaintext
    S.Close();
    double t1=time_from(t0);
    printf("Time=%lf\n",t1/1000000);
    S.PrintCount();
#endif
#endif
    return;
    /*
    float w0, w1, w2;
    __pool__revealFloat(&w0, W);
    __pool__revealFloat(&w1, W+1);
    __pool__revealFloat(&w2, W+2);
    printf("[%f, %f, %f]\n", w0, w1, w2);
    
    __pool__RELEASE__fixpoint(W+0);
    __pool__RELEASE__fixpoint(W+1);
    __pool__RELEASE__fixpoint(W+2);
    __pool__RELEASE__fixpoint(&alpha);
    for (int i = 0; i < data_size; i++) {
        __pool__RELEASE__fixpoint(X1+i);
        __pool__RELEASE__fixpoint(X2+i);
        __pool__RELEASE__fixpoint(y+i);
    }
     */
}
// Debug
// void logreg() {
//     __pool__fixpoint a;
//     __pool__make__fixpoint(&a, 1.23456);
//     __pool__debugPrintFloat(a);
//     __pool__fixpoint b;
//     __pool__make__fixpoint(&b, 2.34567);
//     __pool__debugPrintFloat(b);
//     __pool__fixpoint tmp1;
//     __pool__make__fixpoint(&tmp1, 0.0);
//     __pool__fixpoint__add(&tmp1, &a, &b);
//     __pool__debugPrintFloat(tmp1);
//     __pool__RELEASE__fixpoint(&a);
//     __pool__RELEASE__fixpoint(&b);
//     __pool__RELEASE__fixpoint(&tmp1);
// }

