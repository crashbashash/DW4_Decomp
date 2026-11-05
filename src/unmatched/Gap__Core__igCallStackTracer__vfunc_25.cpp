/* 0x002d4350 - Gap__Core__igCallStackTracer__vfunc_25. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
extern void * DAT_00586dc8[4];
int Gap__Core__igCallStackTracer__vfunc_25(void);
}
class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
int Gap__Core__igCallStackTracer__vfunc_25(void) {
    DW4VC_92_0 *temp_a0;
    temp_a0 = (DW4VC_92_0 *)(*(int *)((char *)(DAT_00586dc8[0]) + 80));
    if (temp_a0 != 0) {
        if (temp_a0->vX() != 0) {
            return 1;
        }
    }
    return 0;
}
