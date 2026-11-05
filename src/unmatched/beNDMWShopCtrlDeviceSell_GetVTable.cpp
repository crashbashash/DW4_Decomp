/* stack-object GetVTable accessor with a string member released through a helper; verified by tools/verify.py.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
typedef struct { int *vt; int w[23]; int s; } Obj;
extern "C" {
int igObject_InitHeader(void *);
int FUN_00226990(void *, int);
int FUN_003b6770(void *, int);
extern int DAT_0053f9b0[4];
extern void * DAT_00586dc8[4];
int beNDMWShopCtrlDeviceSell_GetVTable(void);
}
int beNDMWShopCtrlDeviceSell_GetVTable(void) {
    Obj o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = &DAT_0053f9b0[0];
    o.s = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053f9b0[0];
    FUN_00226990(&o.s, -1);
    FUN_003b6770(&o, 0);
    return r;
}
