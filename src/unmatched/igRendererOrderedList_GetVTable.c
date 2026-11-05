struct Obj { int *vt; int w[7]; };
int igObject_InitHeader(struct Obj *);
int FUN_0044c5e0(struct Obj *, int);
extern int DAT_00541d70[4];
extern void * DAT_00586dc8[4];
int igRendererOrderedList_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.vt = &DAT_00541d70[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00541d70[0];
    FUN_0044c5e0(&obj, 0);
    return r;
}

