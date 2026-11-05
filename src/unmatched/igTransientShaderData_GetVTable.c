struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
int FUN_00194930();
int igObject_InitHeader();
extern int DAT_0052b870[4];
extern void * DAT_00586dc8[4];
int igTransientShaderData_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.fC = 0;
    obj.f10 = 0;
    obj.f14 = 0;
    obj.vt = (&DAT_0052b870[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0052b870[0]);
    FUN_00194930(&obj, 0);
    return temp_s0;
}
