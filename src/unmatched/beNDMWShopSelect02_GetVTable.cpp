extern "C" {
int igObject_InitHeader(void *);
int ObjectRef_Destruct_00150eb0(void *, int);
int FUN_003b4050(void *, int);
extern int DAT_005401b0[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; int f56; int f60; int f64; int f68; int f72; int f76; int f80; int f84; int f88; int f92; int f96; int f100; int f104; int f108; int f112; int f116; int f120; int f124; };
int beNDMWShopSelect02_GetVTable(void) {
    struct Obj o;
    int r;
    igObject_InitHeader(&o);
    o.f52 = 0;
    o.f56 = 0;
    o.f60 = 0;
    o.f64 = 0;
    o.f68 = 0;
    o.f72 = 0;
    o.f76 = 0;
    o.f80 = 0;
    o.f108 = 0;
    o.vt = &DAT_005401b0[0];
    o.f112 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005401b0[0];
    ObjectRef_Destruct_00150eb0(&o.f112, -1);
    FUN_003b4050(&o, 0);
    return r;
}
}
