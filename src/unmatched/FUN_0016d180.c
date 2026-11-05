/* 0x0016d180 — FUN_0016d180. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

void FUN_0016d180(int *arg0, void *arg1)
{
  int new_var;
  new_var = *((int *) (((char *) arg1) + 952));
  *arg0 = 0;
  *arg0 = new_var;
}
