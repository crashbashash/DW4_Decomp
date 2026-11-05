extern "C" {
void Gap__Core__igPsx2LongTimer__vfunc_27(struct S *arg0);
}
class DW4VC_148_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual long long vX(); };
struct S : public DW4VC_148_0 { char pad[4]; long long f8; char pad2[16]; unsigned char f32; };
void Gap__Core__igPsx2LongTimer__vfunc_27(S *arg0) {
    if (arg0->f32 != 0) {
        arg0->f32 = 0;
        arg0->f8 = arg0->vX();
    }
}
