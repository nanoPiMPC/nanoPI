typedef int Index;
typedef int bit;
extern Index Zero;
extern Index One;
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
  for (i = 0; i < 12; i++)
  {
    __pool__RELEASE(z[i]);
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
  bit __tmp__10 = __pool__XOR(x[0], y[0]);
  bit __tmp__9 = __pool__AND(__tmp__10, x[0]);
  __pool__RELEASE(t);
  t = __pool__COPY(__tmp__9);
  for (int i = 1; i < 12; i++)
  {
    __pool__RELEASE(t);
    t = Compare1(x[i], y[i], t);
  }

  __pool__RELEASE(__tmp__9);
  __pool__RELEASE(__tmp__10);
  return t;
}

void add(Index *z, Index *x, Index *y)
{
  Index t = __pool__NewVar();
  bit __tmp__14 = __pool__AND(x[0], y[0]);
  __pool__RELEASE(t);
  t = __pool__COPY(__tmp__14);
  bit __tmp__15 = __pool__XOR(x[0], y[0]);
  __pool__RELEASE(z[0]);
  z[0] = __pool__COPY(__tmp__15);
  int i;
  for (i = 1; i < 12; i++)
  {
    bit __tmp__18 = __pool__XOR(t, x[i]);
    __pool__RELEASE(z[i]);
    z[i] = __pool__COPY(__tmp__18);
    bit __tmp__19 = Mux1(x[i], y[i], z[i]);
    __pool__RELEASE(t);
    t = __pool__COPY(__tmp__19);
    bit __tmp__20 = __pool__XOR(z[i], y[i]);
    __pool__RELEASE(z[i]);
    z[i] = __pool__COPY(__tmp__20);
    __pool__RELEASE(__tmp__18);
    __pool__RELEASE(__tmp__19);
    __pool__RELEASE(__tmp__20);
  }

  __pool__RELEASE(t);
  __pool__RELEASE(__tmp__14);
  __pool__RELEASE(__tmp__15);
}

void add1(Index *z, Index *x, Index y)
{
  Index t = __pool__NewVar();
  bit __tmp__22 = __pool__AND(x[0], y);
  __pool__RELEASE(t);
  t = __pool__COPY(__tmp__22);
  bit __tmp__23 = __pool__XOR(x[0], y);
  __pool__RELEASE(z[0]);
  z[0] = __pool__COPY(__tmp__23);
  int i;
  for (i = 1; i < 12; i++)
  {
    bit __tmp__26 = __pool__XOR(t, x[i]);
    __pool__RELEASE(z[i]);
    z[i] = __pool__COPY(__tmp__26);
    bit __tmp__28 = __pool__XOR(z[i], one);
    bit __tmp__27 = __pool__AND(x[i], __tmp__28);
    __pool__RELEASE(t);
    t = __pool__COPY(__tmp__27);
    __pool__RELEASE(__tmp__26);
    __pool__RELEASE(__tmp__28);
    __pool__RELEASE(__tmp__27);
  }

  __pool__RELEASE(t);
  __pool__RELEASE(__tmp__22);
  __pool__RELEASE(__tmp__23);
}

void ED(Index *z, Index *x, Index *y)
{
  Index matrix0[612]; __pool__NewArray(matrix0, 612);
  Index matrix1[612]; __pool__NewArray(matrix1, 612);
  Index a[48]; __pool__NewArray(a, 48);
  int i;
  int j;
  for (i = 0; i < 12; i++)
  {
    bit __tmp__35 = __pool__COPY(Zero);
    __pool__RELEASE(matrix0[i]);
    matrix0[i] = __pool__COPY(__tmp__35);
    __pool__RELEASE(__tmp__35);
  }

  for (i = 1; i < (50 + 1); i++)
  {
    add1(matrix0 + (i * 12), matrix0 + ((i - 1) * 12), One);
  }

  for (i = 1; i < (50 + 1); i++)
  {
    add1(matrix1, matrix0, One);
    for (j = 1; j < (50 + 1); j++)
    {
      add1(a, &matrix0[j * 12], One);
      add1(&a[12], &matrix1[(j - 1) * 12], One);
      bit __tmp__43 = __pool__XOR(x[2 * (i - 1)], y[2 * (j - 1)]);
      Index tmp1 = __pool__COPY(__tmp__43);
      bit __tmp__44 = __pool__XOR(x[(2 * (i - 1)) + 1], y[(2 * (j - 1)) + 1]);
      Index tmp2 = __pool__COPY(__tmp__44);
      bit __tmp__45 = __pool__AND(tmp1, tmp2);
      Index tmp3 = __pool__COPY(__tmp__45);
      add1(&a[2 * 12], &matrix0[(j - 1) * 12], tmp3);
      bit __tmp__47 = Compare(a, &a[1 * 12]);
      Index tmp4 = __pool__COPY(__tmp__47);
      Mux(&a[3 * 12], a, &a[1 * 12], tmp4);
      bit __tmp__49 = Compare(&a[3 * 12], &a[2 * 12]);
      Index tmp5 = __pool__COPY(__tmp__49);
      Mux(&matrix1[j * 12], &a[3 * 12], &a[2 * 12], tmp5);
      for (int k = 0; k < 12; k++)
      {
        __pool__RELEASE(matrix0[((j - 1) * 12) + k]);
        matrix0[((j - 1) * 12) + k] = __pool__COPY(matrix1[((j - 1) * 12) + k]);
      }

      __pool__RELEASE(__tmp__43);
      __pool__RELEASE(tmp1);
      __pool__RELEASE(__tmp__44);
      __pool__RELEASE(tmp2);
      __pool__RELEASE(__tmp__45);
      __pool__RELEASE(tmp3);
      __pool__RELEASE(__tmp__47);
      __pool__RELEASE(tmp4);
      __pool__RELEASE(__tmp__49);
      __pool__RELEASE(tmp5);
    }

    for (int k = 0; k < 12; k++)
    {
      __pool__RELEASE(matrix0[(50 * 12) + k]);
      matrix0[(50 * 12) + k] = __pool__COPY(matrix1[(50 * 12) + k]);
    }

  }

  for (i = 0; i < 12; i++)
  {
    __pool__RELEASE(z[i]);
    z[i] = __pool__COPY(matrix0[50 + i]);
  }

  __pool__RELEASEArray(matrix0, 612);
  __pool__RELEASEArray(matrix1, 612);
  __pool__RELEASEArray(a, 48);
}

