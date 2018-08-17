#include "float.hpp"
void __pool__initBool(__pool__bool* src) {
        #ifndef USE_CIRCUITS
    src->val = -1;
#endif
    src->bit = __pool__NewVar();
}

void __pool__makeBool(__pool__bool* dst, bool src) {
    __pool__initBool(dst);
     #ifndef USE_CIRCUITS
    dst->val = src;
#endif
    if (src)
    {
        extern Index One;
        dst->bit=__pool__COPY(One);
    }
    else
    {
        extern Index Zero;
        dst->bit=__pool__COPY(Zero);
    }
    
    /*
    #ifdef Simulator
      //  dst->bit = Input((unsigned char) src);
    #else
        dst->bit = src;
    #endif
     */
}

void __pool__revealBool(bool* dst, __pool__bool* src) {
    #ifdef USE_CIRCUITS
        #ifdef Simulator
            *dst = Map.Read(src->bit)->value;
        #else
            *dst = src->bit;
        #endif
    #else
        *dst = src->val;
    #endif
}

void __pool__debugPrintBool(__pool__bool v) {
    bool r;
    __pool__revealBool(&r, &v);
    printf("R: %d\n", r);
}

void __pool__releaseBool(__pool__bool* src) {
    __pool__RELEASE(src->bit);
    src->bit=-1;
}

void __pool__initFloat(__pool__float* src) {
#ifndef USE_CIRCUITS
    src->val = -1;
#endif
    for (int i = 0; i < 32; i++) {
        src->bits[i] = __pool__NewVar();
    }
}

void __pool__makeFloat(__pool__float* dst, float src) {
    __pool__initFloat(dst);
     #ifndef USE_CIRCUITS
    dst->val = src;
#endif
    unsigned char* floatBytes = (unsigned char*) &src;
    int i = 0;
    int j = 0;
    int k = 0;
    unsigned char currentByte = floatBytes[j];
    int size = 32;
    while(size-- > 0) {
/*
#ifdef Simulator
            dst->bits[k] = Input(currentByte & 0x01);
        #else 
            dst->bits[k] = currentByte & 0x01;
        #endif
        */
        if(currentByte & 0x01)
        {
            extern Index One;
            dst->bits[k]=__pool__COPY(One);
        }
        else
        {
            extern Index Zero;
            dst->bits[k]=__pool__COPY(Zero);
        }
        currentByte >>= 1; 
        i++;
        if (i == 8) { 
            i = 0;
            j++;
            currentByte = floatBytes[j];
        }
        k++;
    }
}

void __pool__revealFloat(float* dst, __pool__float* src) {
    int float_byte_size = sizeof(float);
    int byte_size = sizeof(char) * 8;
    int tmp = 0;
    unsigned char floatBytes[float_byte_size];
    memcpy(floatBytes, (unsigned char*) &tmp, float_byte_size);
    int j = 0;
    unsigned char currentByte = floatBytes[j];
    int bit_number;
    for ( int i = 0; i < float_byte_size * byte_size; i++ ) {
        bit_number = i % byte_size;
        #ifdef Simulator
            currentByte |= (Map.Read(src->bits[i])->value<< bit_number);
        #else
            currentByte |= (src->bits[i] << bit_number);
        #endif
        if (bit_number == byte_size - 1) {
            floatBytes[j] = currentByte;
            j++;
            currentByte = floatBytes[j];
        }
    }
    #ifdef USE_CIRCUITS
        memcpy(dst, floatBytes, float_byte_size);
    #else
        *dst = src->val;
    #endif
}

void __pool__releaseFloat(__pool__float* src) {
    for (int i = 0; i < 32; i++)
    {
        __pool__RELEASE(src->bits[i]);
        src->bits[i]=-1;
    }
}

void __pool__debugPrintFloatBits(__pool__float* n) {
    int float_byte_size = sizeof(float);
    int byte_size = sizeof(char) * 8;
    for (int i = 0; i < float_byte_size * byte_size; i++) {
        #ifdef Simulator
            printf("%i", Map.Read(n->bits[i])->value & 1);
        #else
            printf("%i", n->bits[i] & 1);
        #endif
    }
    printf("\n");
}

void __pool__debugPrintFloat(__pool__float v) {
    float r;
    __pool__revealFloat(&r, &v);
    printf("R: %f\n", r);
}
void __pool__COPY__float(__pool__float*dst, __pool__float*src)
{
    __pool__releaseFloat(dst);
    for(int i=0;i<32;i++)
        dst->bits[i]=__pool__COPY(src->bits[i]);    
}

void floatMux(__pool__float *dst,__pool__float *src1,__pool__float *src2,__pool__bool *c)
{
    __pool__COPY__float(dst,src1);
    return;
    
    Index tmp[32];
    for(int i=0;i<32;i++)
    {
        Index tmp1=__pool__XOR(src1->bits[i],src2->bits[i]);
        tmp[i]=__pool__AND(tmp1,c->bit);
        __pool__RELEASE(tmp1);
    }
    for(int i=0;i<32;i++)
    {
        __pool__RELEASE(dst->bits[i]);
        dst->bits[i]=__pool__XOR(tmp[i],src1->bits[i]);
        __pool__RELEASE(tmp[i]);
    }
}

/*
void __pool__floatLt(__pool__bool* dst, __pool__float* op1, __pool__float* op2)
{
    __pool__RELEASE(dst->bit);
    dst->bit=__pool__COPY(op1->bits[0]);
}
*/

void __pool__floatLt(__pool__bool* dst, __pool__float* op1, __pool__float* op2) {
#ifdef USE_CIRCUITS
    __pool__lt_circuit(&dst->bit, op1->bits, op2->bits);
#else
    dst->val = op1->val < op2->val;
#endif
}


/*
void __pool__floatAdd(__pool__float* dst, __pool__float* op1, __pool__float* op2)
{
    __pool__COPY__float(dst,op1);
}
*/

void __pool__floatAdd(__pool__float* dst, __pool__float* op1, __pool__float* op2) {
    #ifdef USE_CIRCUITS
    __pool__releaseFloat(dst);
        __pool__add_circuit(dst->bits, op1->bits, op2->bits);
    #else
        dst->val = op1->val + op2->val;
    #endif
}

/*
void __pool__floatSub(__pool__float* dst, __pool__float* op1, __pool__float* op2)
{
    __pool__COPY__float(dst,op1);
}
*/

void __pool__floatSub(__pool__float* dst, __pool__float* op1, __pool__float* op2) {
    #ifdef USE_CIRCUITS
    __pool__releaseFloat(dst);
        __pool__sub_circuit(dst->bits, op1->bits, op2->bits);
    #else
        dst->val = op1->val - op2->val;
    #endif
}


/*
void __pool__floatMul(__pool__float* dst, __pool__float* op1, __pool__float* op2)
{
    __pool__COPY__float(dst,op1);
}
*/


void __pool__floatMul(__pool__float* dst, __pool__float* op1, __pool__float* op2) {
    #ifdef USE_CIRCUITS
    __pool__releaseFloat(dst);
    __pool__mul_circuit(dst->bits, op1->bits, op2->bits);
    #else
        dst->val = op1->val * op2->val;
    #endif
}



 /*
void __pool__floatDiv(__pool__float* dst, __pool__float* op1, __pool__float* op2) {
    #ifdef USE_CIRCUITS
        __pool__div_circuit(dst->bits, op1->bits, op2->bits);
    #else
        dst->val = op1->val / op2->val;
    #endif
}

 */
