struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00231030(struct Obj *, int);
int FUN_0033dc20(int *, int);
int FUN_0034ca30(int *, int);
int FUN_0034cab0(int *, int);
extern int DAT_0053b030[4];
extern void * DAT_00586dc8[4];
int bePadManager_GetVTable(void);
}
int bePadManager_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_0053b030[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053b030[0];
    FUN_0034cab0(&obj.w6, -1);
    FUN_0034ca30(&obj.w5, -1);
    FUN_0033dc20(&obj.w4, -1);
    FUN_00231030(&obj, 0);
    return t;
}
