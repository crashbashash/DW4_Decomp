struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
int igObject_InitHeader(struct Obj *);
int FUN_00135430();
int FUN_0014aa70();
int ObjectRef_Destruct_001c6460();
int FUN_00233590();
extern int DAT_0052cc20[4];
extern void * DAT_00586dc8[4];
int igDependencyOrderedList_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052cc20[0];
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052cc20[0];
    ObjectRef_Destruct_001c6460(&obj.w5, -1);
    FUN_00135430(&obj.w4, -1);
    FUN_00233590(&obj.w3, -1);
    FUN_0014aa70(&obj.w2, -1);
    return t;
}
