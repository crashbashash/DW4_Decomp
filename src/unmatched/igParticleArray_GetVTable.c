struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
int igObject_InitHeader(struct Obj *);
int FUN_00137260();
int FUN_0014cd10();
int FUN_00130140();
int FUN_001338d0();
int FUN_0014cc90();
extern int DAT_005266c0[4];
extern void * DAT_00586dc8[4];
int igParticleArray_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005266c0[0];
    obj.w2 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    obj.w12 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005266c0[0];
    FUN_00137260(&obj.w17, -1);
    FUN_0014cd10(&obj.w12, -1);
    FUN_00130140(&obj.w11, -1);
    FUN_001338d0(&obj.w10, -1);
    FUN_0014cc90(&obj.w2, -1);
    return t;
}
