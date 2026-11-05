/* 0x00373aa0 — COUNTERget. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

extern "C" {
int beMessenger_SendNamed(int, int *, int, int, int *);
int beMessenger_GetObject(int, int);
void *FUN_003a9250(int, int *);
extern int DAT_0050d8f0[4];
extern int DAT_0050d940[4];
extern int DAT_0050daf8[4];
extern int DAT_0058a1c0[4];
int COUNTERget(int arg0);
}

int COUNTERget(int arg0)
{
  int *new_var;
  beMessenger_SendNamed(DAT_0058a1c0[0, 0], &DAT_0050d940[0], 0, 0, &DAT_0050d8f0[0]);
  new_var = (int *) (((char *) FUN_003a9250(beMessenger_GetObject(DAT_0058a1c0[0], 0), &DAT_0050daf8[0])) + 12);
  return *((int *) ((*((int *) (((char *) (*new_var)) + 16))) + (arg0 * 4)));
}
