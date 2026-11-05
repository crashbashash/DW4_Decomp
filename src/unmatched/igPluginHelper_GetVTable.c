struct Obj { int *vt; int w[7]; };
int igObject_InitHeader(struct Obj *);
int FUN_002bc440(int *, int);
int FUN_002bc4c0(int *, int);
int FUN_002bc540(int *, int);
int StringRef_Destruct_00130720(int *, int);
extern int DAT_0052eee0[4];
extern void * DAT_00586dc8[4];
int igPluginHelper_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052eee0[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052eee0[0];
    FUN_002bc540(&obj.w[4], -1);
    FUN_002bc4c0(&obj.w[3], -1);
    FUN_002bc440(&obj.w[2], -1);
    StringRef_Destruct_00130720(&obj.w[1], -1);
    return t;
}
