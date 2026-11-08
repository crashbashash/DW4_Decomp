int sceIpuRestartDMA();

int FUN_0010a440(void *arg0)
{
  int new_var2;
  int new_var;
  new_var2 = *((int *) (((char *) arg0) + 64));
  new_var = new_var2;
  sceIpuRestartDMA(new_var2 = new_var + 0x68);
  return 1;
}
