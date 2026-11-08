extern "C" {
int fflush(...);
extern void * _impure_ptr[4];
extern void ** DAT_005871b8[4];
void FUN_003046d0(void);
}
class DW4VC_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(); };
void FUN_003046d0(void) {
    if (DAT_005871b8[0] != 0) {
        ((DW4VC_128_0 *)(DAT_005871b8[0]))->vX();
    }
    fflush(*(int *)((char *)(_impure_ptr[0]) + 12));
}
