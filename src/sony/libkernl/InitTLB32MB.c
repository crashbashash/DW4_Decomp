typedef unsigned int u_int;
typedef struct {
    int nkernel;
    int ndefault;
    int nextend;
    int wired;
    u_int (*kernel)[4];
    u_int (*deflt)[4];
    u_int (*extend)[4];
} TlbInfo;
extern TlbInfo D_00482558;
extern char D_004d26d0[];
extern char D_004d2708[];
extern char D_004d2720[];
extern char D_004d2738[];
int FUN_0010d0d0(const char *fmt, ...);
void FUN_001145c8(int code);
int RFU086_WaitEvnetFlag(int index, u_int mask, u_int hi, u_int lo0, u_int lo1);
int InitTLB32MB(void)
{
    register int i asm("$25");
    int n;
    int j;
    u_int (*e)[4];
    FUN_0010d0d0(D_004d26d0, D_00482558.nkernel - 1, D_00482558.nkernel,
                 D_00482558.nkernel + D_00482558.ndefault - 1, D_00482558.nkernel + D_00482558.ndefault,
                 D_00482558.nkernel + D_00482558.ndefault + D_00482558.nextend - 1);
    __asm__ volatile("mtc0 $0, $6\n\tsync.p");
    i = 0;
    n = D_00482558.nkernel;
    if (n > 48) {
        FUN_0010d0d0(D_004d2708);
        FUN_001145c8(1);
    }
    for (e = D_00482558.kernel; i < n; i++, e++)
        RFU086_WaitEvnetFlag(i, (*e)[0], (*e)[1], (*e)[2], (*e)[3]);
    n = i + D_00482558.ndefault;
    if (n > 48) {
        FUN_0010d0d0(D_004d2720);
        FUN_001145c8(1);
    }
    for (e = D_00482558.deflt; i < n; i++, e++)
        RFU086_WaitEvnetFlag(i, (*e)[0], (*e)[1], (*e)[2], (*e)[3]);
    D_00482558.wired = i;
    __asm__ volatile("mtc0 %0, $6\n\tsync.p" : : "r"(i));
    if (D_00482558.nextend > 0) {
        n = i + D_00482558.nextend;
        if (n > 48) {
            FUN_0010d0d0(D_004d2738);
            FUN_001145c8(1);
        }
        for (e = D_00482558.extend; i < n; i++, e++)
            RFU086_WaitEvnetFlag(i, (*e)[0], (*e)[1], (*e)[2], (*e)[3]);
    }
    for (j = i; j < 48; j++)
        RFU086_WaitEvnetFlag(j, 0, 0xe0000000 + (j << 13), 0, 0);
    return i;
}
