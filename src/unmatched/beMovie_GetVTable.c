struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
int igObject_InitHeader(struct Obj *);
int FUN_003369f0();
int FUN_0033f5e0();
int StringRef_Destruct_00130720();
extern int DAT_0053bad0[4];
extern void * DAT_00586dc8[4];
int beMovie_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_0053bad0[0];
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053bad0[0];
    StringRef_Destruct_00130720(&obj.w9, -1);
    FUN_003369f0(&obj.w8, -1);
    FUN_0033f5e0(&obj, 0);
    return t;
}
