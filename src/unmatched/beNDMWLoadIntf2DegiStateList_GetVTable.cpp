extern "C" {
int igObject_InitHeader(int *);
extern int DAT_0053cff0[4];
extern int *DAT_00586dc8[4];
int beNDMWLoadIntf2DegiStateList_GetVTable(void);
}
int beNDMWLoadIntf2DegiStateList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_0053cff0[0];
    off = *(int *)((char *)(DAT_00586dc8[0]) + 916);
    return *(int *)((char *)tmp + off);
}
