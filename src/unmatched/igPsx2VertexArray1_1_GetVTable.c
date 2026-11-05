struct Obj { int *vt; int w[35]; };
int igObject_InitHeader(struct Obj *);
int FUN_00135430(int *, int);
int FUN_00152560(int *, int);
int FUN_001524c0(struct Obj *, int);
extern int DAT_00525190[4];
extern void * DAT_00586dc8[4];
int igPsx2VertexArray1_1_GetVTable(void) {
    struct Obj obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w[5] = 0;
    obj.w[6] = 0;
    obj.vt = &DAT_00525190[0];
    obj.w[11] = 0;
    obj.w[12] = 0;
    obj.w[13] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00525190[0];
    FUN_00152560(&obj.w[13], -1);
    FUN_00135430(&obj.w[12], -1);
    FUN_00135430(&obj.w[11], -1);
    FUN_001524c0(&obj, 0);
    return t;
}
