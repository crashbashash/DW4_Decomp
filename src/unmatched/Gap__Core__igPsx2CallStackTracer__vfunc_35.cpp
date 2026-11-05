extern "C" {
extern int DAT_00587220[4];
void Gap__Core__igPsx2CallStackTracer__vfunc_35(void **arg0);
}
class DW4VC_180_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual int vX(int); };
void Gap__Core__igPsx2CallStackTracer__vfunc_35(void **arg0) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    unsigned int var_s1;
    int temp_a1;
    int *temp_s0;

    var_s1 = 0;
    do {
        temp_s0 = &DAT_00587220[var_s1];
        temp_a1 = *temp_s0;
        if (temp_a1 != 0) {
            ((DW4VC_180_1 *)(arg0))->vX((int)(temp_a1));
            *temp_s0 = 0;
        }
        var_s1 += 1;
    } while (var_s1 < 0x40U);
}
