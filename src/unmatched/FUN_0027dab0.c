int DTX_CallUrpc();
extern int sjrmt_sbuf[4];
extern int DAT_005708c0[4];
int FUN_0027dab0(int arg0, int arg1, int arg2, int *arg3) {
    *(int *)((char *)&(sjrmt_sbuf[0]) + 0) = arg0;
    *(int *)((char *)&(sjrmt_sbuf[0]) + 4) = arg1;
    *(int *)((char *)&(sjrmt_sbuf[0]) + 8) = arg2;
    DTX_CallUrpc(0x2A, &sjrmt_sbuf[0], 3, &DAT_005708c0[0], 1);
    *arg3 = *(int *)((char *)&(DAT_005708c0[0]) + 4);
    return *(int *)((char *)&(DAT_005708c0[0]) + 0);
}
