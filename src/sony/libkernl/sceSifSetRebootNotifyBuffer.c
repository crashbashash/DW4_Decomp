extern void *rebootNotifyTable;
extern int rebootNotifyCount;
int DIntr(void);
int EIntr(void);
void *FUN_0012724c(void *p, int c, unsigned int n);
void *sceSifSetRebootNotifyBuffer(void *tbl, int n) {
    int s;
    void *old;
    s = DIntr();
    old = rebootNotifyTable;
    rebootNotifyTable = tbl;
    rebootNotifyCount = n;
    FUN_0012724c(tbl, 0, n << 4);
    if (s) EIntr();
    return old;
}
