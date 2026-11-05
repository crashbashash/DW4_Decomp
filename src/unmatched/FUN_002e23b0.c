/* 0x002e23b0 — FUN_002e23b0. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

int FUN_002e23b0(void *arg0, int arg1)
{
  int var_v0;
  var_v0 = 0;
  if (arg1 < 0x10)
  {
    var_v0 = arg1 * 2;
    var_v0 = (((unsigned int) (*((int *) (((char *) arg0) + 80)))) >> var_v0) & 3;
  }
  return var_v0;
}
