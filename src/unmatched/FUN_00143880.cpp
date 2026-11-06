extern "C" {
extern int DAT_0055f5b0[4];
extern void ** DAT_0055f5b8[4];
void FUN_00143880(int (*arg0)(int));
}
struct DW4SR4 { int w0; };
class DW4VCSR_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual DW4SR4 vX(int); };
void FUN_00143880(int (*arg0)(int)) {
    DW4SR4 sp2C;

loop_1:
    sp2C = ((DW4VCSR_132_1 *)(DAT_0055f5b8[0]))->vX((int)(1));
    arg0(DAT_0055f5b0[0]);
    goto loop_1;
}
