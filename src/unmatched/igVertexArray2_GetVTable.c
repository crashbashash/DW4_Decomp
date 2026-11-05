struct Obj { int *vt; int w[7]; };
int FUN_00131bc0();
int FUN_0014aa70();
int FUN_0014aaf0();
int ObjectRef_Destruct_001363f0();
int igObject_InitHeader(struct Obj *);
extern int DAT_00526410[4];
extern void * DAT_00586dc8[4];
int igVertexArray2_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &DAT_00526410[0];
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00526410[0];
    FUN_0014aaf0(&obj.w[4], -1);
    FUN_0014aa70(&obj.w[3], -1);
    ObjectRef_Destruct_001363f0(&obj.w[2], -1);
    FUN_00131bc0(&obj, 0);
    return r;
}
