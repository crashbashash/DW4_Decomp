extern int D_004f5990[];
extern void FUN_002b3b38(void *h, int a, int *tbl);
int FUN_002b5068(unsigned int bits) {
    int r;
    switch (bits) {
    case 16: r = 1; break;
    case 24: r = 2; break;
    case 32: r = 3; break;
    case 8:
    default:
        FUN_002b3b38(0, 0, D_004f5990);
        r = 0;
        break;
    }
    return r;
}
