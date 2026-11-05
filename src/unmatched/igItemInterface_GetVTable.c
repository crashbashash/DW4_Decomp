struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
int igObject_InitHeader(struct Obj *);
int FUN_00227e70();
int FUN_00227df0();
int FUN_0013a880();
int FUN_00227d70();
extern int DAT_0052c0f0[4];
extern void * DAT_00586dc8[4];
int igItemInterface_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c0f0[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052c0f0[0];
    FUN_00227e70(&obj.w11, -1);
    FUN_00227df0(&obj.w10, -1);
    FUN_0013a880(&obj.w9, -1);
    FUN_00227d70(&obj.w8, -1);
    return t;
}
