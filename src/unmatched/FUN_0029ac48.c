/* 0x0029ac48 — FUN_0029ac48. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

void *FUN_00294a30();
void FUN_0029ac48(void)
{
  int (*temp_v1)(int);
  void *temp_v0;
  int new_var;
  temp_v0 = (void *) FUN_00294a30();
  new_var = *((int *) (((char *) temp_v0) + 84));
  temp_v1 = (int (*)(int)) (*((int *) (((char *) temp_v0) + 80)));
  if (temp_v1 != 0)
  {
    temp_v1(new_var);
  }
}
