extern "C" {
extern int DAT_00586818[4];
extern int DAT_005610b0[4];
extern int DAT_00561098[4];
int FUN_00162ca0(void *arg0);
}
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct O { int p0; int p4; int p8; DW4VC_88_0 *obj; int p10; int p14; int f18; };
int FUN_00162ca0(void *a0) {
    O *arg0 = (O *)a0;
    if (DAT_00586818[0] == arg0->obj->vX()) {
        return arg0->f18;
    }
    if (DAT_005610b0[0] == arg0->obj->vX()) {
        return 3;
    }
    if (DAT_00561098[0] == arg0->obj->vX()) {
        return 4;
    }
    return 0;
}
