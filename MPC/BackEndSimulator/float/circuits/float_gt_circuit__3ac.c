
void __pool__gt_circuit(Index *dest, Index *op2)
{
  __pool__le_circuit(dest, op2);
  __pool__neg_circuit(dest, dest);
}

