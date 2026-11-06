struct Obj { int *vt; int w[11]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0033ec80(int *, int);
int FUN_00343260(int *, int);
int FUN_00359bd0(int *, int);
int FUN_00359c50(int *, int);
extern int DAT_00536b70[4];
extern void * DAT_00586dc8[4];
int beMatCtrlInfo_GetVTable(void);
}
int beMatCtrlInfo_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_00536b70[0];
    obj.w[6] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00536b70[0];
    FUN_00359c50(&obj.w[8], -1);
    FUN_00359bd0(&obj.w[7], -1);
    FUN_00343260(&obj.w[6], -1);
    FUN_0033ec80((int *)&obj, 0);
    return t;
}
