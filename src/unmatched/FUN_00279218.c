void FUN_002659a0(const char *format, ...);
extern char DAT_004f1540[];
extern char DAT_004f1570[];
extern char DAT_004f15a0[];
extern int DAT_004b1de8;
extern int DAT_004b1dec;
extern int DAT_004b1dc4;
extern int DAT_004b1dc8;
extern int DAT_004b1dc0;

void FUN_00279218(int nste, int nmono)
{
    int n;

    if (nste < 0) {
        FUN_002659a0(DAT_004f1540, nste);
        return;
    }
    if (nmono < 0) {
        FUN_002659a0(DAT_004f1570, nmono);
        return;
    }
    n = nste * 2 + nmono;
    if (n > 32) {
        FUN_002659a0(DAT_004f15a0, 32);
        return;
    }
    DAT_004b1dc0 = n;
    DAT_004b1de8 = nste;
    DAT_004b1dec = nmono;
    DAT_004b1dc4 = n * 0x4100;
    DAT_004b1dc8 = 1;
}
