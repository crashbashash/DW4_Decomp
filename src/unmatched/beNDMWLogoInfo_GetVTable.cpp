/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct W { int *vt; int f[7]; };
extern "C" {
int FUN_0033ec80(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_0053d370[4];
extern char *DAT_00586dc8[4];
int beNDMWLogoInfo_GetVTable(void);
}
int beNDMWLogoInfo_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[1] = 0;
    o.f[4] = 0;
    o.f[5] = 0;
    o.vt = DAT_0053d370;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053d370;
    FUN_0033ec80(&o, 0);
    return r;
}
