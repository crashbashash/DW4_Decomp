extern "C" {
int igObject_InitHeader(void *);
int ObjectRef_Destruct_00150eb0(void *, int);
int beNDMWWindowCtrl_Destroy(void *, int);
extern int DAT_0053ed50[4];
extern void *DAT_00586dc8[4];
struct Obj { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; int f56; int f60; int f64; int f68; int f72; int f76; int f80; int f84; int f88; int f92; };
int beNDMWStatusCtrlBit_GetVTable(void) {
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
    o.vt = &DAT_0053ed50[0];
    o.f84 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_0053ed50[0];
    ObjectRef_Destruct_00150eb0(&o.f84, -1);
    beNDMWWindowCtrl_Destroy(&o, 0);
    return r;
}
}
