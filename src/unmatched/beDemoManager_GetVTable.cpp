extern "C" {
int igObject_InitHeader(void *);
int FUN_00363400(void *, int);
int FUN_00363380(void *, int);
int FUN_00231030(void *, int);
extern int DAT_0053a460[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char t[4]; };
int beDemoManager_GetVTable(void) {
    struct Obj o;
    int r;
    igObject_InitHeader(&o);
    o.vt = &DAT_0053a460[0];
    o.f8 = 0;
    o.f24 = 0;
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053a460[0];
    FUN_00363400(&o.f28, -1);
    FUN_00363380(&o.f24, -1);
    FUN_00231030(&o, 0);
    return r;
}
}
