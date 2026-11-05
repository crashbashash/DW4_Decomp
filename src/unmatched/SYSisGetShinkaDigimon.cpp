/* 0x003725f0 — SYSisGetShinkaDigimon. m2c draft + decomp-permuter search, verified
 * byte-identical to retail by tools/verify.py. */

extern "C" {
int bePlayer_GetStruct(int);
void *igProperty_GetRecordArray(int, int *);
extern int DAT_0050da18[4];
unsigned char SYSisGetShinkaDigimon(int arg0, int arg1);
}

unsigned char SYSisGetShinkaDigimon(int arg0, int arg1)
{
  char *new_var;
  new_var = ((char *) igProperty_GetRecordArray(bePlayer_GetStruct(arg0 + 1), &DAT_0050da18[0])) + 12;
  return *((int *) ((*((int *) (((char *) (*((int *) new_var))) + 16))) + arg1));
}
