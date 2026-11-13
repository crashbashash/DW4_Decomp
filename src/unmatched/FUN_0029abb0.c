void *mwsfd_GetWork();
void FUN_0029abb0(void)
{
  int new_var;
  int (*temp_v1)(int);
  void *temp_v0;
  temp_v0 = (void *) mwsfd_GetWork();
  temp_v1 = (int (*)(int)) (*((int *) (((char *) temp_v0) + 64)));
  new_var = *((int *) (((char *) temp_v0) + 68));
  if (temp_v1 != 0)
  {
    temp_v1(new_var);
  }
}
