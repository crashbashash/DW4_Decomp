/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct W { int *vt; int f[27]; };
extern "C" {
int beNDMWWindowCtrl_Destroy(struct W *, int);
int igObject_InitHeader(struct W *);
extern int DAT_0053fd30[4];
extern char *DAT_00586dc8[4];
int beNDMWShopCtrl50_GetVTable(void);
}
int beNDMWShopCtrl50_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[12] = 0;
    o.f[13] = 0;
    o.f[14] = 0;
    o.f[15] = 0;
    o.f[16] = 0;
    o.f[17] = 0;
    o.f[18] = 0;
    o.vt = DAT_0053fd30;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_0053fd30;
    beNDMWWindowCtrl_Destroy(&o, 0);
    return r;
}
