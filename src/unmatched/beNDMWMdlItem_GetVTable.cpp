extern "C" {
int igObject_InitHeader(void *);
int FUN_0014aa70(void *, int);
int FUN_003bf2f0(void *, int);
extern int DAT_00540450[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; int f56; int f60; };
int beNDMWMdlItem_GetVTable(void) {
    struct Obj o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f24 = 0;
    o.vt = &DAT_00540450[0];
    o.f48 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00540450[0];
    FUN_0014aa70(&o.f48, -1);
    FUN_003bf2f0(&o, 0);
    return r;
}
}
