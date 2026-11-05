struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
int igObject_InitHeader(struct Obj *);
int FUN_0014dd40();
int FUN_00194790();
int FUN_0019eb40();
extern int DAT_0052a8e0[4];
extern void * DAT_00586dc8[4];
int igInterpretedShaderData_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.vt = &DAT_0052a8e0[0];
    obj.w6 = 0;
    obj.w7 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052a8e0[0];
    FUN_0014dd40(&obj.w7, -1);
    FUN_0019eb40(&obj.w6, -1);
    FUN_00194790(&obj, 0);
    return t;
}
