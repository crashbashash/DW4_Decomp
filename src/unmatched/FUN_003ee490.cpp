extern "C" {

int memcpy(int, int, unsigned int);
int beNDMWDegiData__UpdateFieldsFromData(void *);
void FUN_003ee490(void *arg0, void *arg1)
{
  unsigned int new_var;
  new_var = *((int *) (((char *) arg0) + 36));
  memcpy(*((int *) (((char *) arg0) + 28)), *((int *) (((char *) arg1) + 28)), new_var);
  beNDMWDegiData__UpdateFieldsFromData(arg0);
}
}
