struct Obj { int *vt; int w[7]; };
extern "C" {
int FUN_0019c220(int *, int);
int FUN_00341160(int *, int);
int FUN_00343260(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_005349d0[4];
extern void * DAT_00586dc8[4];
int beCameraBoxData_GetVTable(void);
}
int beCameraBoxData_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005349d0[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005349d0[0];
    FUN_00341160(&obj.w[5], -1);
    FUN_00341160(&obj.w[4], -1);
    FUN_00341160(&obj.w[3], -1);
    FUN_0019c220(&obj.w[2], -1);
    FUN_00343260(&obj.w[1], -1);
    return r;
}
