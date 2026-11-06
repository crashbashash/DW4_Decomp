struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; int w24; int w25; int w26; int w27; int w28; int w29; int w30; int w31; int w32; int w33; int w34; int w35; int w36; int w37; int w38; int w39; int w40; int w41; int w42; int w43; int w44; int w45; int w46; int w47; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_001338d0(int *, int);
int FUN_001354b0(int *, int);
int FUN_0033e920(struct Obj *, int);
int FUN_003401c0(int *, int);
int FUN_00340240(int *, int);
int ObjectRef_Destruct_00150eb0(int *, int);
extern int DAT_00539a70[4];
extern void * DAT_00586dc8[4];
int beWaterPlainInfoRam_GetVTable(void);
}
int beWaterPlainInfoRam_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w10 = 0;
    obj.vt = &DAT_00539a70[0];
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w23 = 0;
    obj.w38 = 0;
    obj.w44 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00539a70[0];
    FUN_00340240(&obj.w44, -1);
    FUN_003401c0(&obj.w38, -1);
    ObjectRef_Destruct_00150eb0(&obj.w23, -1);
    FUN_001354b0(&obj.w22, -1);
    FUN_001338d0(&obj.w21, -1);
    FUN_0033e920(&obj, 0);
    return t;
}
