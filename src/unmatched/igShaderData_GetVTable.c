struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
int igObject_InitHeader(struct Obj *);
int FUN_0013a800();
int FUN_00194830();
int FUN_001948b0();
extern int DAT_00528870[4];
extern void * DAT_00586dc8[4];
int igShaderData_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00528870[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00528870[0];
    FUN_00194830(&obj.w5, -1);
    FUN_001948b0(&obj.w4, -1);
    FUN_0013a800(&obj.w3, -1);
    FUN_0013a800(&obj.w2, -1);
    return t;
}
