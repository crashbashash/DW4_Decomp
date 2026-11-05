struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
int igObject_InitHeader(struct Obj *);
int FUN_0013a880();
int FUN_001d35d0();
int FUN_00225b90();
int StringRef_Destruct_00130720();
extern int DAT_0052be10[4];
extern void * DAT_00586dc8[4];
int igOptInterface_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052be10[0];
    obj.w8 = 0;
    obj.w9 = 0;
    obj.w10 = 0;
    obj.w11 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052be10[0];
    FUN_001d35d0(&obj.w11, -1);
    FUN_00225b90(&obj.w10, -1);
    StringRef_Destruct_00130720(&obj.w9, -1);
    FUN_0013a880(&obj.w8, -1);
    return t;
}
