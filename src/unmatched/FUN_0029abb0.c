/* 0x0029abb0 — FUN_0029abb0. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

void *FUN_00294a30();
void FUN_0029abb0(void)
{
  int new_var;
  int (*temp_v1)(int);
  void *temp_v0;
  temp_v0 = (void *) FUN_00294a30();
  temp_v1 = (int (*)(int)) (*((int *) (((char *) temp_v0) + 64)));
  new_var = *((int *) (((char *) temp_v0) + 68));
  if (temp_v1 != 0)
  {
    temp_v1(new_var);
  }
}
