int memset();
int FUN_001ee1c0();
int FUN_00330730();
struct S4 { int w0; union { int w; struct { unsigned lo:31; unsigned a:1; } b; } u; int w8; int wc; };
extern struct S4 DAT_00490c20[1];
extern int DAT_00568e70[4];
extern int DAT_00568e90[4];
extern int DAT_00568e94[4];
extern int DAT_00568e98[4];
extern int DAT_00568e9c[4];
extern int DAT_00568ea0[4];
extern int DAT_00568eb8[4];
void FUN_001ee600(void) {
    int *s0;
    int *s1;
    int *s2;

    s2 = (int *)DAT_00568eb8[0];
    DAT_00568eb8[0] = FUN_001ee1c0();
    s0 = (int *)DAT_00568eb8[0];
    s0[5] = 0;
    s0[6] = (int)s2;
    *(long long *)s0 = 0;
    s2[5] = (int)s0;
    s1 = (int *)DAT_00568ea0[0];
    memset(&DAT_00568e70[0], 0, 0x48);
    DAT_00568e90[0] = FUN_00330730(0x8000, 0xB);
    DAT_00568ea0[0] = DAT_00568e90[0];
    DAT_00568e94[0] = DAT_00568e90[0] + 0x7FF0;
    DAT_00568e98[0] = DAT_00568e94[0] - 0x1400;
    DAT_00568e9c[0] = DAT_00568e98[0];
    s0[3] = DAT_00568e90[0];
    DAT_00490c20[0].u.b.lo = DAT_00568e90[0];
    s1[0] = DAT_00490c20[0].w0;
    s1[1] = DAT_00490c20[0].u.w;
    s1[2] = DAT_00490c20[0].w8;
    s1[3] = DAT_00490c20[0].wc;
    s2[4] = (int)(s1 + 4);
}
