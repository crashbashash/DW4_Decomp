void *FUN_00294a30();
void FUN_0029abe0(void)
{
  int (*temp_v1)(int);
  void *temp_v0;
  int new_var;
  temp_v0 = (void *) FUN_00294a30();
  new_var = *((int *) (((char *) temp_v0) + 76));
  temp_v1 = (int (*)(int)) (*((int *) (((char *) temp_v0) + 72)));
  if (temp_v1 != 0)
  {
    temp_v1(new_var);
  }
}
