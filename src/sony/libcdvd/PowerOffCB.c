extern int DAT_00483564;
extern int DAT_00483580;
int FUN_00113f20(void);
int FUN_00113f78(void);
void sceSifAddCmdHandler(unsigned int cid, void (*handler)(void *, void *), void *arg);
void _sceCd_Poff_Intr(void *pkt, void *arg);
int PowerOffCB(void) {
    int s;
    DAT_00483564 = 1;
    s = FUN_00113f20();
    sceSifAddCmdHandler(0x80000012, _sceCd_Poff_Intr, 0);
    if (s) FUN_00113f78();
    DAT_00483564 = 0;
    DAT_00483580 = 1;
    return 1;
}
