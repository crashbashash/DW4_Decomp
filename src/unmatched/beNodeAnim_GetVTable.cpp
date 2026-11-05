extern "C" {
int igObject_InitHeader(void *);
int FUN_00195a90(void *, int);
int FUN_00195a90(void *, int);
extern int DAT_005381b0[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; int f56; int f60; int f64; int f68; int f72; int f76; int f80; int f84; int f88; int f92; int f96; int f100; int f104; int f108; };
int beNodeAnim_GetVTable(void) {
    struct Obj o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f12 = 0;
    o.f16 = 0;
    o.f28 = 0;
    o.vt = &DAT_005381b0[0];
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_005381b0[0];
    
    FUN_00195a90(&o, 0);
    return r;
}
}
