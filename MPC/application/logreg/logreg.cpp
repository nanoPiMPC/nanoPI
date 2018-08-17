#include <string.h>
#ifndef Simulator
#include "Stage.hpp"
#else
#include "BackendSimulator.hpp"
#endif
#include "float.hpp"
extern Index Zero,One;
#define Dim 10
#define MaxDim 10
__pool__float Fzero,Fone,Fhalf,Ft1,Ft2;
void sigmoid(__pool__float *dst,__pool__float *v) {
    __pool__bool test1, test2;
    __pool__float tmp1, tmp2;
    __pool__float tmp;
    __pool__initFloat(&tmp);
    __pool__initBool(&test1);
    __pool__initBool(&test2);
    __pool__floatLt(&test1, &Ft1,v);
    __pool__floatLt(&test2, &Ft2,v);
    floatMux(&tmp,&Fzero,&Fhalf,&test1);
    floatMux(dst,&tmp,&Fhalf,&test2);
    __pool__releaseBool(&test1);
    __pool__releaseBool(&test2);
    __pool__releaseFloat(&tmp);

}

void hyp(__pool__float *dst,__pool__float x[], __pool__float* W) {
    __pool__float tmp,SUM,tmp1;
    __pool__initFloat(&(tmp));
    __pool__initFloat(&(SUM));
    __pool__initFloat(&(tmp1));
    __pool__floatMul(&(tmp), &(W[1]), &(x[0]));
    __pool__floatAdd(&SUM, &(tmp), W);
    for(int i=1;i<Dim;i++)
    {
        __pool__floatMul(&tmp, &(W[i+1]), &(x[i]));
        __pool__releaseFloat(&tmp1);
        __pool__floatAdd(&tmp1, &SUM, &(tmp));
        __pool__COPY__float(&SUM,&tmp1);

    }
    __pool__releaseFloat(&(tmp1));
    __pool__releaseFloat(&(tmp));
    sigmoid(dst,&SUM);
    __pool__releaseFloat(&(SUM));
    return;
}
void sgd(__pool__float*  W,int size, __pool__float* X, __pool__float* y, __pool__float alpha, int n) {
    for (int ep = 0; ep < n; ep++) {
        for (int i = 0; i < size; i++) {
            printf("ep %d i=%d\n",ep,i);
            __pool__float yhat;
            __pool__initFloat(&yhat);
        
            hyp(&yhat,&(X[i*Dim]), W);
            //dy=(yhat - y[i])
            // W[0] = W[0] - (alpha * dy);
            __pool__float dy, tmp1;
            __pool__initFloat(&tmp1);
            __pool__initFloat(&dy);
            __pool__floatSub(&dy, &yhat, y+i);
            __pool__floatMul(&tmp1, &alpha, &dy);
            __pool__releaseFloat(&yhat);
            __pool__COPY__float(&yhat,W);
            __pool__floatSub(W, &yhat, &tmp1);
            __pool__releaseFloat(&tmp1);
            __pool__releaseFloat(&yhat);
            
            
            for(int d=1;d<=Dim;d++)
            {
                // W[d] = W[d] - (alpha * X[i,d] * dy);
                __pool__float tmp1, tmp2;
                __pool__initFloat(&tmp1);
                __pool__initFloat(&tmp2);
                __pool__floatMul(&tmp1, &alpha, &(X[i*Dim+d-1]));
                __pool__floatMul(&tmp2, &dy, &tmp1);
                __pool__releaseFloat(&tmp1);
                __pool__COPY__float(&tmp1,W+d);
                __pool__floatSub(W+d,&tmp1, &tmp2);
                __pool__releaseFloat(&tmp2);
                __pool__releaseFloat(&tmp1);
            }
            __pool__releaseFloat(&dy);

        }
    }
    return;
}
void Application() {
    Zero=S.StageMap->Zero;
    One=S.StageMap->One;
    static const int data_size = 10;
    __pool__makeFloat(&Fzero,0.0);
    __pool__makeFloat(&Fone,1.0);
    __pool__makeFloat(&Fhalf,0.5);
    
    __pool__makeFloat(&Ft1,0.5);
    __pool__makeFloat(&Ft2,-0.5);
    
    
    __pool__float* X1 = (__pool__float*) malloc(sizeof(__pool__float)*data_size*Dim);
    float X1_data[MaxDim] = {2.7810836, 1.465489372, 3.396561688,
        1.38807019, 3.06407232, 7.627531214,
        5.332441248, 6.922596716, 8.675418651,
        7.673756466};
    for (int i = 0; i < Dim; i++)
        __pool__makeFloat(X1+i, X1_data[i]);
    
    __pool__float* X2=X1;
    for(int i=1;i<data_size;i++)
    {
        X2 = X2+Dim;
        float X2_data[MaxDim] = {2.550537003, 2.362125076, 4.400293529,
            1.850220317, 3.005305973, 2.759262235,
            2.088626775, 1.77106367, -0.242068655,
            3.508563011};
        for (int i = 0; i < Dim; i++)
            __pool__makeFloat(X2+i, X2_data[i]);
    }
    __pool__float* y = (__pool__float*) malloc(sizeof(__pool__float)*data_size);
    float y_data[data_size] = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 1.0};
    for (int i = 0; i < data_size; i++)
        __pool__makeFloat(y+i, y_data[i]);
    
    
    int iterations = 10;
    __pool__float alpha;
    __pool__makeFloat(&alpha, 1);
    __pool__float* W = (__pool__float*) malloc(sizeof(__pool__float)*(Dim+1));
    for(int d=0;d<=Dim;d++)
        __pool__makeFloat(W+d, 0.0);

    __pool_InputFlush();
//    test(X1);
    auto t0=clock_start();
    sgd(W,data_size, X1, y, alpha, iterations);
    S.Close();
    double t1=time_from(t0);
    printf("Time=%lf\n",t1/1000000);
    S.PrintCount();
    return;
    /*
    float w0, w1, w2;
    __pool__revealFloat(&w0, W);
    __pool__revealFloat(&w1, W+1);
    __pool__revealFloat(&w2, W+2);
    printf("[%f, %f, %f]\n", w0, w1, w2);
    
    __pool__releaseFloat(W+0);
    __pool__releaseFloat(W+1);
    __pool__releaseFloat(W+2);
    __pool__releaseFloat(&alpha);
    for (int i = 0; i < data_size; i++) {
        __pool__releaseFloat(X1+i);
        __pool__releaseFloat(X2+i);
        __pool__releaseFloat(y+i);
    }
     */
}
// Debug
// void logreg() {
//     __pool__float a;
//     __pool__makeFloat(&a, 1.23456);
//     __pool__debugPrintFloat(a);
//     __pool__float b;
//     __pool__makeFloat(&b, 2.34567);
//     __pool__debugPrintFloat(b);
//     __pool__float tmp1;
//     __pool__makeFloat(&tmp1, 0.0);
//     __pool__floatAdd(&tmp1, &a, &b);
//     __pool__debugPrintFloat(tmp1);
//     __pool__releaseFloat(&a);
//     __pool__releaseFloat(&b);
//     __pool__releaseFloat(&tmp1);
// }

