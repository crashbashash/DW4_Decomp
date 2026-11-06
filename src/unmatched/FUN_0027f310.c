int FUN_0027f200();
int FUN_0027f310(void *arg0)
{
  int new_var2;
  int *new_var;
  new_var = (int *) (((char *) arg0) + (44 & 0xFFFFFFFFFFFFFFFF));
  new_var2 = FUN_0027f200();
  new_var2 = new_var2 + (*new_var);
  return new_var2 + (*((int *) (((char *) arg0) + 56)));
}
