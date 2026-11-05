int iReferSemaStatus();
int iSignalSema();
long long p2readGSPrivRegister();
extern int DAT_0056bf80[4];
extern int DAT_0056bfc0[4];
extern int DAT_0056c010[4];
void FUN_002080b0(void) {
    int st[8];

    DAT_0056c010[0] += 1;
    DAT_0056bfc0[0] = (int) ((long long) (p2readGSPrivRegister(0x48) << 0x20) >> 0x20);
    iReferSemaStatus(DAT_0056bf80[0], st);
    if (st[0] != st[1]) {
        iSignalSema(DAT_0056bf80[0]);
    }
}
