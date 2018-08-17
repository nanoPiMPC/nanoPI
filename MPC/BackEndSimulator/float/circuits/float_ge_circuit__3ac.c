#ifndef POOL_FLOAT_GE_H
#define POOL_FLOAT_GE_H
void __pool__ge_circuit(Index *dest, Index *op2)
{
  __pool__lt_circuit(dest, op2);
  __pool__neg_circuit(dest, dest);
}
#endif
