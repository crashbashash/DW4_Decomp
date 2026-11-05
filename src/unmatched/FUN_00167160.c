/* 0x00167160 — FUN_00167160. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

int FUN_00167160(int arg0, int arg1)
{
  int new_var;
  new_var = arg1 * 4;
  return *((int *) (((char *) (new_var + arg0)) + 240));
}
