struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; };
int igObject_InitHeader(struct Obj *);
int FUN_00226990();
int FUN_003b6090();
int FUN_003b6770();
extern int DAT_0053f8e0[4];
extern void * DAT_00586dc8[4];
int beNDMWShopCtrlSales_GetVTable(void) {
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
    obj.vt = &DAT_0053f8e0[0];
    obj.w24 = 0;
    obj.w25 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053f8e0[0];
    FUN_00226990(&obj.w25, -1);
    FUN_003b6090(&obj.w24, -1);
    FUN_003b6770(&obj, 0);
    return t;
}
