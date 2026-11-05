struct Obj { int *vt; int w[11]; };
int FUN_0013a880();
int FUN_001489a0();
int FUN_0014dd40();
int FUN_00198190();
int igObject_InitHeader(struct Obj *);
extern int DAT_0052a4a0[4];
extern void * DAT_00586dc8[4];
int igBoundingBoxesMaker_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a4a0[0];
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052a4a0[0];
    FUN_0013a880(&obj.w[8], -1);
    FUN_001489a0(&obj.w[7], -1);
    FUN_0014dd40(&obj.w[5], -1);
    FUN_00198190(&obj.w[4], -1);
    return r;
}
