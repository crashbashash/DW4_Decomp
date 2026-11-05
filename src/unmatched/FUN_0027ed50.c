extern int DAT_00570bc0[4];
int *FUN_0027ed50(int arg0, int arg1) {
    *(int *)((char *)&(DAT_00570bc0[0]) + 4) = arg1;
    *(int *)((char *)&(DAT_00570bc0[0]) + 0) = arg0;
    return &DAT_00570bc0[0];
}
