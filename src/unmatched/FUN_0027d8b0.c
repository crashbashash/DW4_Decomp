int DTX_CallUrpc();
extern int DAT_00570780[4];
extern int sjrmt_sbuf[4];
extern int DAT_005708c0[4];
int *FUN_0027d8b0(int arg0) {
    sjrmt_sbuf[0] = arg0;
    DTX_CallUrpc(0x24, &sjrmt_sbuf[0], 1, &DAT_005708c0[0], 4);
    *(int *)((char *)&(DAT_00570780[0]) + 0) = (int)((int) *(int *)((char *)&(DAT_005708c0[0]) + 0));
    *(int *)((char *)&(DAT_00570780[0]) + 4) = (int)((int) *(int *)((char *)&(DAT_005708c0[0]) + 4));
    *(int *)((char *)&(DAT_00570780[0]) + 8) = (int)((int) *(int *)((char *)&(DAT_005708c0[0]) + 8));
    *(int *)((char *)&(DAT_00570780[0]) + 12) = (int)((int) *(int *)((char *)&(DAT_005708c0[0]) + 12));
    return &DAT_00570780[0];
}
