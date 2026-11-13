int DTX_CallUrpc();
extern int sjrmt_sbuf[4];
extern int DAT_005708c0[4];
int FUN_0027d780(int arg0, int arg1, int arg2) {
    *(int *)((char *)&(sjrmt_sbuf[0]) + 0) = arg0;
    *(int *)((char *)&(sjrmt_sbuf[0]) + 4) = arg1;
    *(int *)((char *)&(sjrmt_sbuf[0]) + 8) = arg2;
    DTX_CallUrpc(0x20, &sjrmt_sbuf[0], 3, &DAT_005708c0[0], 1);
    return DAT_005708c0[0];
}
