extern int DAT_00483564;
extern int DAT_00483580;
int FUN_00113f20(void);
int FUN_00113f78(void);
void FUN_0010d4c8(unsigned int cid, void (*handler)(void *, void *), void *arg);
void FUN_00116670(void *pkt, void *arg);
int FUN_001166c8(void) {
    int s;
    DAT_00483564 = 1;
    s = FUN_00113f20();
    FUN_0010d4c8(0x80000012, FUN_00116670, 0);
    if (s) FUN_00113f78();
    DAT_00483564 = 0;
    DAT_00483580 = 1;
    return 1;
}
