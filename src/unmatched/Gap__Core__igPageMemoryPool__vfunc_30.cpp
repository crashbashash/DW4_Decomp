struct R { int v; };
class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual R vB(int); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void vA(); char pad4[108]; unsigned char f112; char pad113[27]; int f140; };
extern "C" {
void Gap__Core__igPageMemoryPool__vfunc_30(C *arg0);
}
void Gap__Core__igPageMemoryPool__vfunc_30(C *arg0) {
    if (arg0->f112 == 0) {
        arg0->vA();
        arg0->f112 = 1;
        if (arg0->f140 & 4) {
            R r = arg0->vB(1);
        }
    }
}
