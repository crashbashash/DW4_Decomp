int FUN_002b3c78(int arg0, int arg1)
{
  int new_var;
  new_var = arg1;
  new_var = new_var * 4;
  new_var = new_var + arg0;
  return *((int *) (((char *) new_var) + 64));
}
