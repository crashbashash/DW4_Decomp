/* 0x0029ea88 — FUN_0029ea88. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

int FUN_0029ea88(int arg0, int arg1)
{
  int new_var;
  new_var = arg0;
  new_var = new_var + (arg1 * 0x74);
  return *((int *) (((char *) new_var) + 4884));
}
