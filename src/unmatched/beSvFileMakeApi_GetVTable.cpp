struct Obj { int *vt; int w[263]; };
extern "C" {
int FUN_00348390(struct Obj *, int);
int FUN_003484b0(int *, int);
int FUN_00349080(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_0053c000[4];
extern void * DAT_00586dc8[4];
int beSvFileMakeApi_GetVTable(void);
}
int beSvFileMakeApi_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[11] = 0;
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.vt = &DAT_0053c000[0];
    obj.w[15] = 0;
    obj.w[16] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053c000[0];
    FUN_003484b0(&obj.w[16], -1);
    FUN_00349080(&obj.w[15], -1);
    FUN_00348390(&obj, 0);
    return r;
}
