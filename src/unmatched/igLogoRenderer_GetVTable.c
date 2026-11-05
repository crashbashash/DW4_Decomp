struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
int igObject_InitHeader(struct Obj *);
int FUN_001353b0();
int FUN_0013bfe0();
int FUN_0019ab10();
int FUN_00230f70();
extern int DAT_00542230[4];
extern void * DAT_00586dc8[4];
int igLogoRenderer_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00542230[0];
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00542230[0];
    FUN_0013bfe0(&obj.w8, -1);
    FUN_0019ab10(&obj.w7, -1);
    FUN_001353b0(&obj.w6, -1);
    FUN_00230f70(&obj, 0);
    return t;
}
