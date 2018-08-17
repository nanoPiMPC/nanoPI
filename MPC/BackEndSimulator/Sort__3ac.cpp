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
#define Length 32
Index Mux1(Index x, Index y, Index c)
{
  bit __tmp__3 = __pool__XOR(x, y);
  bit __tmp__2 = __pool__AND(c, __tmp__3);
  bit __tmp__1 = __pool__XOR(x, __tmp__2);
  __pool__RELEASE(__tmp__2);
  __pool__RELEASE(__tmp__3);
  return __tmp__1;
}

void Mux(Index *z, Index *x, Index *y, Index c)
{
  int i;
  for (i = 0; i < Length; i++)
  {
    z[i] = Mux1(x[i], y[i], c);
  }

}

Index Compare1(Index x, Index y, Index c)
{
  bit __tmp__7 = __pool__XOR(x, y);
  bit __tmp__6 = Mux1(c, x, __tmp__7);
  __pool__RELEASE(__tmp__7);
  return __tmp__6;
}

Index Compare(Index *x, Index *y)
{
  Index t = __pool__NewVar();
  int i;
  bit __tmp__11 = __pool__XOR(x[0], y[0]);
  bit __tmp__10 = __pool__AND(__tmp__11, x[0]);
  __pool__RELEASE(t);
  t = __pool__COPY(__tmp__10);
  for (i = 1; i < Length; i++)
  {
    __pool__RELEASE(t);
    t = Compare1(x[i], y[i], t);
  }

  __pool__RELEASE(__tmp__10);
  __pool__RELEASE(__tmp__11);
  return t;
}

void Swap(Index *In1, Index *In2, Index c)
{
    Index tmp[Length];
    __pool__NewArray(tmp,Length);
    Index tmp1[Length];
    __pool__NewArray(tmp1,Length);
  Mux(tmp, In1, In2, c);
  int i;
  for (i = 0; i < Length; i++)
  {
    bit __tmp__19 = __pool__XOR(tmp[i], In1[i]);
    __pool__RELEASE(tmp1[i]);
    tmp1[i] = __pool__COPY(__tmp__19);
    bit __tmp__20 = __pool__XOR(tmp1[i], In2[i]);
      __pool__RELEASE(In2[i]);
    In2[i] = __pool__COPY(__tmp__20);
     __pool__RELEASE(In1[i]);
      In1[i] = __pool__COPY(tmp[i]);
    __pool__RELEASE(__tmp__19);
    __pool__RELEASE(__tmp__20);
  }
  __pool__RELEASEArray(tmp, Length);
  __pool__RELEASEArray(tmp1, Length);
}

void SortCompare(Index Sign, Index *In, int len)
{
  int dist = len / 2;
  Index tmp = __pool__NewVar();
  int i;
  for (i = 0; i < dist; i++)
  {
    bit __tmp__26 = Compare(&In[Length * i], &In[(Length * i) + dist]);
    __pool__RELEASE(tmp);
    tmp = __pool__COPY(__tmp__26);
    bit __tmp__27 = __pool__XOR(Sign, tmp);
    __pool__RELEASE(tmp);
    tmp = __pool__COPY(__tmp__27);
    Swap(&In[i * Length], &In[(i + dist) * Length], tmp);
    __pool__RELEASE(__tmp__26);
    __pool__RELEASE(__tmp__27);
  }

  __pool__RELEASE(tmp);
}

void SortMerge(Index Sign, Index *In, int len)
{
  if (len == 1)
    return;

  SortCompare(Sign, In, len);
  SortMerge(Sign, In, len / 2);
  SortMerge(Sign, &In[(Length * len) / 2], len / 2);
}

void Sort(Index Sign, Index *In, int len)
{
  if (len <= 1)
    return;
  Sort(One, In, len / 2);
  Sort(Zero, &In[(Length * len) / 2], len / 2);
  SortMerge(Sign, In, len);
}

