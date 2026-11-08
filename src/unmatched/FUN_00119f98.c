extern int *DAT_0055d5e8;
extern int *DAT_0055d5ec;
extern int *DAT_0055d5f0;
extern int DAT_00485198;
int FUN_0010af10(int sema);
void FUN_00119f98(unsigned int arg) {
    int *r;
    r = (int *)(arg | 0x20000000);
    if (DAT_0055d5e8) *DAT_0055d5e8 = r[0];
    if (DAT_0055d5ec) *DAT_0055d5ec = r[1];
    if (DAT_0055d5f0) *DAT_0055d5f0 = r[36];
    FUN_0010af10(DAT_00485198);
}
