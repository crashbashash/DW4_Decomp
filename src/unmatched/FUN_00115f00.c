extern void *DAT_00483528;
extern int DAT_0048352c;
int FUN_00113f20(void);
int FUN_00113f78(void);
void *FUN_0012724c(void *p, int c, unsigned int n);
void *FUN_00115f00(void *tbl, int n) {
    int s;
    void *old;
    s = FUN_00113f20();
    old = DAT_00483528;
    DAT_00483528 = tbl;
    DAT_0048352c = n;
    FUN_0012724c(tbl, 0, n << 4);
    if (s) FUN_00113f78();
    return old;
}
