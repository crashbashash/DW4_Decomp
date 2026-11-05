/* 0x002b03d0 — FUN_002b03d0. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

int FUN_002b03d0(int arg0, int arg1)
{
  arg0 = arg0 + (arg1 * 0x44);
  return *((int *) (((char *) arg0) + 7980));
}
