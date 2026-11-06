int FUN_00273820();
extern int DAT_005707c0[4];
extern int DAT_005708c0[4];
int FUN_0027d7d8(int arg0, int arg1) {
    *(int *)((char *)&(DAT_005707c0[0]) + 0) = arg0;
    *(int *)((char *)&(DAT_005707c0[0]) + 4) = arg1;
    FUN_00273820(0x21, &DAT_005707c0[0], 2, &DAT_005708c0[0], 1);
    return DAT_005708c0[0];
}
