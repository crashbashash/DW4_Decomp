extern int DAT_00483564;
extern int DAT_00483580;
int DIntr(void);
int EIntr(void);
void sceSifAddCmdHandler(unsigned int cid, void (*handler)(void *, void *), void *arg);
void _sceCd_Poff_Intr(void *pkt, void *arg);
int PowerOffCB(void) {
    int s;
    DAT_00483564 = 1;
    s = DIntr();
    sceSifAddCmdHandler(0x80000012, _sceCd_Poff_Intr, 0);
    if (s) EIntr();
    DAT_00483564 = 0;
    DAT_00483580 = 1;
    return 1;
}
