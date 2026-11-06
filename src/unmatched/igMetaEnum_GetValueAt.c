int igMetaEnum_GetValueAt(void *arg0, int arg1)
{
  int *new_var;
  void *temp_a0;
  temp_a0 = (void *) (*((int *) (((char *) arg0) + 16)));
  if (temp_a0 != 0)
  {
    if ((arg1 >= 0) && (arg1 < (*((int *) (((char *) temp_a0) + 8)))))
    {
      return *(new_var = (int *) ((*((int *) (((char *) temp_a0) + 16))) + (arg1 * 4)));
    }
  }
  return 0;
  return 0;
}
