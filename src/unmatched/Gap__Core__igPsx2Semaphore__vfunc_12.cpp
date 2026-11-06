extern "C" {
int Gap__Core__igObject__vfunc_10(...);
void Gap__Core__igPsx2Semaphore__vfunc_12(void **arg0);
}
struct DW4SR4 { int w0; };
class DW4VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
class DW4VCSR_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual DW4SR4 vX(); };
void Gap__Core__igPsx2Semaphore__vfunc_12(void **arg0) {
    DW4SR4 sp2C;

    if (((DW4VC_100_0 *)(arg0))->vX() != 0) {
        sp2C = ((DW4VCSR_96_0 *)(arg0))->vX();
    }
    Gap__Core__igObject__vfunc_10(arg0);
}
