int List_Resize();
extern int DAT_004fb410[4];
void Gap__Core__igLocationTable__vfunc_24(int *arg0, void *arg1, int arg2)
{
  int temp_a1;
  void *temp_a0;
  temp_a0 = (void *) (*((int *) (((char *) arg1) + 16)));
  temp_a1 = arg2 * 5;
  if (temp_a1 >= 0)
  {
    if (temp_a1 <= (*((int *) (((char *) temp_a0) + 12))))
    {
      *((int *) (((char *) temp_a0) + 8)) = temp_a1;
    }
    else
    {
      List_Resize(temp_a0, temp_a1, 4);
    }
  }
  *arg0 = DAT_004fb410[0];
}
