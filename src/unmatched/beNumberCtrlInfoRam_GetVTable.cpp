/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct W { int *vt; int f[19]; };
extern "C" {
int igObject_InitHeader(struct W *);
int FUN_001971e0(int *, int);
int FUN_0033e920(struct W *, int);
int FUN_0034d640(int *, int);
int FUN_0034d6c0(int *, int);
extern int DAT_005384d0[4];
extern void * DAT_00586dc8[4];
int beNumberCtrlInfoRam_GetVTable(void);
}
int beNumberCtrlInfoRam_GetVTable(void) {
    struct W o;
    int *p16;
    int r;
    int *p17;

    igObject_InitHeader(&o);
    o.f[9] = 0;
    o.vt = &DAT_005384d0[0];
    p16 = &o.f[10];
    *p16 = 0;
    p17 = &o.f[14];
    *p17 = 0;
    o.f[15] = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005384d0[0];
    FUN_0034d6c0(&o.f[15], -1);
    FUN_0034d640(p17, -1);
    FUN_001971e0(p16, -1);
    FUN_0033e920(&o, 0);
    return r;
}
