struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; };
extern "C" {
int FUN_00131b20(struct Obj *, int);
int FUN_00366d80(int *, int);
int StringRef_Destruct_00130720(int *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_00534ef0[4];
extern void * DAT_00586dc8[4];
int beCriFxInfo_GetVTable(void);
}
int beCriFxInfo_GetVTable(void) {
    struct Obj obj;
    int r;
    int *pb;
    int *pa;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.vt = &DAT_00534ef0[0];
    pa = &obj.f14;
    *pa = 0;
    pb = &obj.f20;
    *pb = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_00534ef0[0];
    FUN_00366d80(pb, -1);
    StringRef_Destruct_00130720(pa, -1);
    FUN_00131b20(&obj, 0);
    return r;
}
