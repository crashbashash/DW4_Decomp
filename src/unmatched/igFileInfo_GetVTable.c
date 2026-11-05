struct Obj { int *vt; int w[7]; };
int FUN_00131bc0();
int FUN_001d35d0();
int FUN_001d36d0();
int FUN_00228fc0();
int FUN_00229040();
int igObject_InitHeader(struct Obj *);
extern int DAT_0052c170[4];
extern void * DAT_00586dc8[4];
int igFileInfo_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.vt = &DAT_0052c170[0];
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0052c170[0];
    FUN_00229040(&obj.w[5], -1);
    FUN_00228fc0(&obj.w[4], -1);
    FUN_001d35d0(&obj.w[3], -1);
    FUN_001d36d0(&obj.w[2], -1);
    FUN_00131bc0(&obj, 0);
    return r;
}
