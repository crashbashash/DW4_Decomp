struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int ObjectRef_Destruct_001c6460(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
int beNDMWWindowCtrl_Destroy(struct Obj *, int);
extern int DAT_0053fc10[4];
extern void * DAT_00586dc8[4];
int beNDMWShopCtrlA1_GetVTable(void);
}
int beNDMWShopCtrlA1_GetVTable(void) {
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
    obj.vt = &DAT_0053fc10[0];
    obj.w21 = 0;
    obj.w22 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053fc10[0];
    ObjectRef_Destruct_00150eb0(&obj.w22, -1);
    ObjectRef_Destruct_001c6460(&obj.w21, -1);
    beNDMWWindowCtrl_Destroy(&obj, 0);
    return t;
}
