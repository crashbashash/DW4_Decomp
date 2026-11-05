/* 0x0029ea48 — FUN_0029ea48. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

int FUN_0029ea48(int arg0, int arg1)
{
  int *new_var;
  arg0 = arg0 + (arg1 * 0x74);
  new_var = &(*((int *) (((char *) arg0) + 4880)));
  return *new_var;
}
