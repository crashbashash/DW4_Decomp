struct IGB;
extern "C" {
void *FUN_002d7e90(IGB *, int);
int Gap__Core__igIGBFile__vfunc_34(IGB *o);
}
class VCa { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(int, int); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int v264(int); };
class VCb { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int v164(void *); };
struct HDR { char pad32[32]; int f32; unsigned short f36; };
struct IGB { char pad8[8]; int f8; char pad12[92]; HDR *f104; char pad108[48]; int f156; char pad160[4]; int f164; char pad168[88]; int f256; int f260; int f264; int f268; int f272; char pad276[4]; VCa *f280; };
int Gap__Core__igIGBFile__vfunc_34(IGB *o) {
    int i;
    o->f260 = o->f164;
    if (o->f260 < 0) {
        o->f260 = o->f104->f32;
    }
    if (o->f156 < o->f260) {
        o->f260 = o->f156;
    }
    o->f264 = o->f280->v220(o->f260, o->f104->f36);
    o->f256 = 0;
    o->f268 = 0;
    o->f272 = o->f260;
    for (i = 0; i < o->f8; i++) {
        ((VCb *)FUN_002d7e90(o, i))->v164(o);
    }
    o->f280->v264(o->f264);
    o->f264 = 0;
    return 1;
}
