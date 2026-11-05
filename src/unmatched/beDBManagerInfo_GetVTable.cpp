extern "C" {
int igObject_InitHeader(void *);
int FUN_00365e90(void *, int);
int FUN_0033ec80(void *, int);
extern int DAT_005350f0[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
int beDBManagerInfo_GetVTable(void) {
    struct Obj o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f20 = 0;
    o.f24 = 0;
    o.vt = &DAT_005350f0[0];
    o.f28 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005350f0[0];
    FUN_00365e90(&o.f28, -1);
    FUN_0033ec80(&o, 0);
    return r;
}
}
