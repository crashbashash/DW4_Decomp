struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
int igObject_InitHeader(struct Obj *);
int FUN_004501f0();
int FUN_00450270();
int FUN_004502f0();
int FUN_00450370();
extern int DAT_00541300[4];
extern void * DAT_00586dc8[4];
int igGuiComponent_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541300[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00541300[0];
    FUN_00450370(&obj.w7, -1);
    FUN_004502f0(&obj.w5, -1);
    FUN_00450270(&obj.w4, -1);
    FUN_004501f0(&obj.w3, -1);
    return t;
}
