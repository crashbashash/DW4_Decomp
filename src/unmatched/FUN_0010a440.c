/* 0x0010a440 — FUN_0010a440. m2c draft + decomp-permuter search, then verified
 * byte-identical to retail by tools/verify.py (see tools/permuter_one.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0010a640();

int FUN_0010a440(void *arg0)
{
  int new_var2;
  int new_var;
  new_var2 = *((int *) (((char *) arg0) + 64));
  new_var = new_var2;
  FUN_0010a640(new_var2 = new_var + 0x68);
  return 1;
}
