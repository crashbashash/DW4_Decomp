/* 0x002b03e8 — FUN_002b03e8. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

int FUN_002b03e8(int arg0, int arg1)
{
  int new_var2;
  char *new_var;
  new_var2 = arg0;
  new_var2 = new_var2 + (arg1 * 0x44);
  if (1)
  {
    new_var = ((char *) new_var2) + 7988;
    return (*((int *) new_var)) != 0;
  }
}
