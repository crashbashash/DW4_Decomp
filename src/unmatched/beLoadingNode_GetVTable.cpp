struct Obj { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; int f20; int f24; int f28; int f2C; int f30; int f34; int f38; int f3C; int f40; int f44; int f48; int f4C; int f50; int f54; int f58; int f5C; int f60; int f64; int f68; int f6C; int f70; int f74; int f78; int f7C; };
extern "C" {
int FUN_0034e690(struct Obj *, int);
int igObject_InitHeader(struct Obj *);
extern int DAT_00538110[4];
extern void * DAT_00586dc8[4];
int beLoadingNode_GetVTable(void);
}
int beLoadingNode_GetVTable(void) {
    struct Obj obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.fC = 0;
    obj.f10 = 0;
    obj.f1C = 0;
    obj.vt = (&DAT_00538110[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = (&DAT_00538110[0]);
    FUN_0034e690(&obj, 0);
    return temp_s0;
}
