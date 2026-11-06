struct Obj { int *vt; int w[7]; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_0033ec80(void *, int);
int FUN_00343260(void *, int);
extern int DAT_00539490[4];
extern void * DAT_00586dc8[4];
int beSwitchCtrlInfo_GetVTable(void);
}
int beSwitchCtrlInfo_GetVTable(void) {
    struct Obj obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_00539490[0];
    obj.w[6] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00539490[0];
    FUN_00343260(&obj.w[6], -1);
    FUN_0033ec80(&obj, 0);
    return r;
}
