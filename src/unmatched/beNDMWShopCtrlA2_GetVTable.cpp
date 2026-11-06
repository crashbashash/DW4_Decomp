/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int beNDMWWindowCtrl_Destroy(struct Obj *, int);
extern int DAT_0053fbb0[4];
extern void * DAT_00586dc8[4];
int beNDMWShopCtrlA2_GetVTable(void);
}
int beNDMWShopCtrlA2_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053fbb0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053fbb0[0];
    beNDMWWindowCtrl_Destroy(&obj, 0);
    return t;
}
