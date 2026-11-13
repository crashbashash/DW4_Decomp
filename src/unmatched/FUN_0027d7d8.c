int DTX_CallUrpc();
extern int sjrmt_sbuf[4];
extern int DAT_005708c0[4];
int FUN_0027d7d8(int arg0, int arg1) {
    *(int *)((char *)&(sjrmt_sbuf[0]) + 0) = arg0;
    *(int *)((char *)&(sjrmt_sbuf[0]) + 4) = arg1;
    DTX_CallUrpc(0x21, &sjrmt_sbuf[0], 2, &DAT_005708c0[0], 1);
    return DAT_005708c0[0];
}
