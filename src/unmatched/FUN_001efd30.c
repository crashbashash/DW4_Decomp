/* 0x001efd30 - FUN_001efd30. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int FUN_00204240();
extern int *DAT_005691b8[4];
void FUN_001efd30(int arg0) {
    int i;
    int *p;
    p = DAT_005691b8[0];
    i = 0;
    while (i < arg0) {
        if (p == 0) break;
        p = (int *)p[3];
        i += 1;
    }
    if (i != arg0) {
        FUN_00204240(7, &DAT_005691b8[0], i);
    }
}
