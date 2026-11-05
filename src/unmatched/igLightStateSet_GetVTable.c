struct Obj { int *vt; int w[11]; };
int igObject_InitHeader(struct Obj *);
int FUN_00195a90(void *, int);
int FUN_0019d9e0(void *, int);
extern int DAT_00528bc0[4];
extern void * DAT_00586dc8[4];
int igLightStateSet_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[6] = 0;
    obj.vt = &DAT_00528bc0[0];
    obj.w[7] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00528bc0[0];
    FUN_0019d9e0(&obj.w[7], -1);
    FUN_00195a90(&obj, 0);
    return r;
}
