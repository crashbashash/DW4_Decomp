/* stack-object GetVTable accessor with zeroed members and a trailing destructor call.py. C++
 * translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
typedef struct { int *vt; int w[23]; } Obj;
extern "C" {
int igObject_InitHeader(void *);
int beNDMWWindowCtrl_Destroy(void *, int);
extern int DAT_0053fa80[4];
extern void * DAT_00586dc8[4];
int beNDMWShopCtrlEditBit_GetVTable(void);
}
int beNDMWShopCtrlEditBit_GetVTable(void) {
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
    o.vt = &DAT_0053fa80[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053fa80[0];
    beNDMWWindowCtrl_Destroy(&o, 0);
    return r;
}
