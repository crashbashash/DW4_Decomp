struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
int igObject_InitHeader(struct Obj *);
int FUN_0014ec50();
int FUN_001c7600();
int ObjectRef_Destruct_001363f0();
int StringRef_Destruct_00130720();
extern int DAT_0052b950[4];
extern void * DAT_00586dc8[4];
int igDataPump_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b950[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052b950[0];
    FUN_001c7600(&obj.w6, -1);
    StringRef_Destruct_00130720(&obj.w5, -1);
    StringRef_Destruct_00130720(&obj.w4, -1);
    FUN_0014ec50(&obj.w3, -1);
    ObjectRef_Destruct_001363f0(&obj.w2, -1);
    return t;
}
