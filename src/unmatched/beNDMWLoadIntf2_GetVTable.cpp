struct Obj { int *vt; int w[11]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0033dda0(int *, int);
int FUN_0033f5e0(struct Obj *, int);
extern int DAT_0053e860[4];
extern void * DAT_00586dc8[4];
int beNDMWLoadIntf2_GetVTable(void);
}
int beNDMWLoadIntf2_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053e860[0];
    obj.w[8] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e860[0];
    FUN_0033dda0(&obj.w[8], -1);
    FUN_0033f5e0(&obj, 0);
    return r;
}
