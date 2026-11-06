struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0033dda0(int *, int);
int FUN_0033f5e0(struct Obj *, int);
int FUN_003b2a10(int *, int);
extern int DAT_0053e9a0[4];
extern void * DAT_00586dc8[4];
int beNDMWTitle2_GetVTable(void);
}
int beNDMWTitle2_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053e9a0[0];
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e9a0[0];
    FUN_003b2a10(&obj.w9, -1);
    FUN_0033dda0(&obj.w8, -1);
    FUN_0033f5e0(&obj, 0);
    return t;
}
