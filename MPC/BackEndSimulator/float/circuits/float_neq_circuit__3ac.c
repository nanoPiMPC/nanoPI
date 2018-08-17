
void __pool__neq_circuit(Index *dest, Index *op2)
{
  __pool__eq_circuit(dest, op2);
  __pool__neg_circuit(dest, dest);
}

