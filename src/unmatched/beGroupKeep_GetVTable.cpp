struct Obj { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" {
int igObject_InitHeader(struct Obj *);
int FUN_00195a90(struct Obj *, int);
extern int DAT_005360b0[4];
extern void * DAT_00586dc8[4];
int beGroupKeep_GetVTable(void);
}
int beGroupKeep_GetVTable(void) {
    struct Obj obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w7 = 0;
    obj.vt = &DAT_005360b0[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_005360b0[0];
    FUN_00195a90(&obj, 0);
    return t;
}
