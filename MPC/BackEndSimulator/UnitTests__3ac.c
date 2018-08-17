#include "BackendSimulator.hpp"
typedef int Index;
typedef int bit;
extern Index Zero;
extern Index One;
void test(Index dst_array[], Index c, Index constc)
{
    Index a = __pool__NewVar();// [1]
    Index b = __pool__AND(c, constc);
    __pool__RELEASE(a); //[7]
    a = __pool__COPY(c); //[6]
    c = __pool__XOR(constc, b); //[5]
    Index array[32];
    __pool__NewArray(array,32); //[2]
    __pool__RELEASE(dst_array[0]); //[7] [3][4](dst_array[0] is guaranteed to be initialized, it is also treated as if a local static array.
    dst_array[0] = __pool__COPY(a); //[6]
    int i;
    int j;
    for (i = 1; i < 32; i++)
    {
        if(i%2==0)
        {
            Index d=__pool__AND(dst_array[i],c);
            Index small_array[4];
            __pool__NewArray(small_array,4);//[2]
            for(j=0;j<3;j++)
            {
                __pool__RELEASE(small_array[i]); //[7]
                small_array[i]=__pool__COPY(a); //[6]
            }
            __pool__RELEASEArray(small_array,4);//[9]
            __pool__RELEASE(array[i]); //[7]
            array[i]=__pool__COPY(d);// [6]
            __pool__RELEASE(d); //[8] this is the lase use of d in this scope
        }
    }
    __pool__RELEASEArray(array,32); //[9]
    __pool__RELEASE(c); //[7]
    c=__pool__XOR(a,b);
    __pool__RELEASE(a); //[8]
    __pool__RELEASE(b); //[8]
    __pool__RELEASE(c); //[8] [5] since c is reassigned with a new value at line 10. But constc hasn't never been assigned a new value in this scope.
}


