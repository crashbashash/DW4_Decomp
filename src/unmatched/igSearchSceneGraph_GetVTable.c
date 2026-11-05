struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
int FUN_00131bc0();
int FUN_0019c840();
int FUN_002293d0();
int StringRef_Destruct_00130720();
int igObject_InitHeader();
extern int DAT_0052d0d0[4];
extern void * DAT_00586dc8[4];
int igSearchSceneGraph_GetVTable(void) {
    struct Obj obj;

    int temp_s2;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = (&DAT_0052d0d0[0]);
    obj.fC = 0;
    obj.f10 = 0;
    obj.f14 = 0;
    temp_s2 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_0052d0d0[0]);
    FUN_0019c840(&obj.f14, -1);
    StringRef_Destruct_00130720(&obj.f10, -1);
    FUN_002293d0(&obj.fC, -1);
    FUN_00131bc0(&obj, 0);
    return temp_s2;
}
