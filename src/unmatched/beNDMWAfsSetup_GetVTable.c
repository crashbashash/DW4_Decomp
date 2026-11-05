struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
int igObject_InitHeader(struct Obj *);
int FUN_001d35d0();
int FUN_00231030();
int FUN_0025a2b0();
int FUN_003cafa0();
extern int DAT_0053dfa0[4];
extern void * DAT_00586dc8[4];
int beNDMWAfsSetup_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053dfa0[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053dfa0[0];
    FUN_003cafa0(&obj.w7, -1);
    FUN_0025a2b0(&obj.w6, -1);
    FUN_0025a2b0(&obj.w5, -1);
    FUN_001d35d0(&obj.w4, -1);
    FUN_00231030(&obj, 0);
    return t;
}
