//
//  PlaintextSimulator.hpp
//  
//
//  Created by Sourgroup on 4/22/18.
//

#ifndef PlaintextSimulator_hpp
#define PlaintextSimulator_hpp

#include <stdio.h>
#include <stdlib.h>
typedef bool Index;
typedef bool bit;
inline Index __pool__XOR(Index x, Index y)
{
    extern long long XORCount;
    XORCount++;
    return x^y;
}
inline Index __pool__AND(Index x, Index y)
{
    extern long long ANDCount;
    ANDCount++;
    return x&y;
}
inline Index __pool__COPY(Index x)
{
    return x;
}
inline void __pool__RELEASE(Index x)
{
    return;
}
inline Index __pool__NOT(Index x)
{
    return x^1;
}inline Index __pool__OR(Index x, Index y)
{
    return 1^((x^1)&(y^1));
}
inline Index Input()
{
    return 1;
}
inline Index Input(unsigned char value)
{
    return value&1;
}

inline Index __pool__NewVar()
{
    return 0;
}
inline void __pool__NewArray(Index array[],int size)
{
    return;
}
inline void __pool__RELEASEArray(Index array[],int size)
{
    return;
}
#endif /* PlaintextSimulator_hpp */
