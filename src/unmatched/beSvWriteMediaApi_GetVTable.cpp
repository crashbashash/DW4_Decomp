struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00348390(struct Obj *, int);
int FUN_003484b0(int *, int);
int FUN_00349080(int *, int);
extern int DAT_0053bdd0[4];
extern void * DAT_00586dc8[4];
int beSvWriteMediaApi_GetVTable(void);
}
int beSvWriteMediaApi_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w12 = 0;
    obj.w13 = 0;
    obj.w14 = 0;
    obj.vt = &DAT_0053bdd0[0];
    obj.w16 = 0;
    obj.w17 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053bdd0[0];
    FUN_003484b0(&obj.w17, -1);
    FUN_00349080(&obj.w16, -1);
    FUN_00348390(&obj, 0);
    return t;
}
