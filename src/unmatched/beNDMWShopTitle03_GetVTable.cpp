/* C++ translation unit: the unit compiled with exceptions on and retail keeps this function's
 * exception index record, which only the C++ front end emits. */
struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_003b3030(struct Obj *, int);
extern int DAT_00540300[4];
extern void * DAT_00586dc8[4];
int beNDMWShopTitle03_GetVTable(void);
}
int beNDMWShopTitle03_GetVTable(void) {
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
    obj.vt = &DAT_00540300[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00540300[0];
    FUN_003b3030(&obj, 0);
    return t;
}
