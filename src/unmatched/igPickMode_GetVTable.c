struct Obj { int *vt; int w[44]; };
int igMatrix44f_SetIdentity();
int FUN_0019e3c0();
int FUN_001d6560();
int FUN_0044e1e0();
int FUN_0044ee80();
int FUN_00459860();
int FUN_00459ae0();
int igObject_InitHeader(struct Obj *);
extern int DAT_00542720[4];
extern int DAT_00542960[4];
extern void * DAT_00586dc8[4];
int igPickMode_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00542960[0];
    igMatrix44f_SetIdentity(&obj.w[2]);
    obj.vt = &DAT_00542720[0];
    obj.w[18] = 0;
    obj.w[19] = 0;
    obj.w[20] = 0;
    obj.w[21] = 0;
    obj.w[23] = 0;
    obj.w[24] = 0;
    obj.w[27] = 0;
    igMatrix44f_SetIdentity(&obj.w[28]);
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00542720[0];
    FUN_001d6560(&obj.w[27], -1);
    FUN_0019e3c0(&obj.w[24], -1);
    FUN_0044ee80(&obj.w[23], -1);
    FUN_0044e1e0(&obj.w[21], -1);
    FUN_0044e1e0(&obj.w[20], -1);
    FUN_00459ae0(&obj.w[19], -1);
    FUN_00459860(&obj.w[18], -1);
    return r;
}
