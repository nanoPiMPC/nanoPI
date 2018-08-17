#ifndef POOL_FLOAT_H
#define POOL_FLOAT_H
#define USE_CIRCUITS
#include "Stage.hpp"
#include "string.h"
#include <stdio.h>
#include "circuits/pool_test_circuit.hpp"
#include "circuits/float_add_circuit__3ac.hpp"
#include "circuits/float_sub_circuit__3ac.hpp"
#include "circuits/float_mul_circuit__3ac.hpp"
#include "circuits/float_lt_circuit__3ac.hpp"
/*
#include "circuits/float_div_circuit__3ac.c"
*/
typedef struct {
#ifndef USE_CIRCUITS
    float val;
#endif
    Index bits[32];
} __pool__float;

typedef struct {
#ifndef USE_CIRCUITS
    bool val;
#endif
    Index bit;
} __pool__bool;

void __pool__initBool(__pool__bool* src);

void __pool__makeBool(__pool__bool* dst, bool src);

void __pool__revealBool(bool* dst, __pool__bool* src);

void __pool__debugPrintBool(__pool__bool v);

void __pool__releaseBool(__pool__bool* src);

void __pool__initFloat(__pool__float* src);

void __pool__makeFloat(__pool__float* dst, float src);

void __pool__revealFloat(float* dst, __pool__float* src) ;

void __pool__releaseFloat(__pool__float* src);

void __pool__debugPrintFloatBits(__pool__float* n);

void __pool__debugPrintFloat(__pool__float v);
void __pool__COPY__float(__pool__float*dst, __pool__float*src);

void floatMux(__pool__float *dst,__pool__float *src1,__pool__float *src2,__pool__bool *c);

/*
void __pool__floatLt(__pool__bool* dst, __pool__float* op1, __pool__float* op2)
{
    __pool__RELEASE(dst->bit);
    dst->bit=__pool__COPY(op1->bits[0]);
}
*/

void __pool__floatLt(__pool__bool* dst, __pool__float* op1, __pool__float* op2);

/*
void __pool__floatAdd(__pool__float* dst, __pool__float* op1, __pool__float* op2)
{
    __pool__COPY__float(dst,op1);
}
*/

void __pool__floatAdd(__pool__float* dst, __pool__float* op1, __pool__float* op2);

/*
void __pool__floatSub(__pool__float* dst, __pool__float* op1, __pool__float* op2)
{
    __pool__COPY__float(dst,op1);
}
*/

void __pool__floatSub(__pool__float* dst, __pool__float* op1, __pool__float* op2);


/*
void __pool__floatMul(__pool__float* dst, __pool__float* op1, __pool__float* op2)
{
    __pool__COPY__float(dst,op1);
}
*/


void __pool__floatMul(__pool__float* dst, __pool__float* op1, __pool__float* op2);

 /*
void __pool__floatDiv(__pool__float* dst, __pool__float* op1, __pool__float* op2) {
    #ifdef USE_CIRCUITS
        __pool__div_circuit(dst->bits, op1->bits, op2->bits);
    #else
        dst->val = op1->val / op2->val;
    #endif
}

 */

#endif
