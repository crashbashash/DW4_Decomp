struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
int igObject_InitHeader(struct Obj *);
int FUN_001958f0();
int FUN_0019b1f0();
int FUN_00131aa0();
int FUN_00198210();
int FUN_00131b20();
extern int DAT_005288e0[4];
extern void * DAT_00586dc8[4];
int igSceneInfo_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_005288e0[0];
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w15 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005288e0[0];
    FUN_001958f0(&obj.w15, -1);
    FUN_0019b1f0(&obj.w7, -1);
    FUN_00131aa0(&obj.w6, -1);
    FUN_00198210(&obj.w5, -1);
    FUN_00131b20(&obj, 0);
    return t;
}
