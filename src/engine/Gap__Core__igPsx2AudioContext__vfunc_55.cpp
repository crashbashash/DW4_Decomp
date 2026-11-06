/* IgPsx2AudioContext vtable slot 55. Forwards the request to FUN_00300db0, passing the context
 * itself, the caller's value, and the result of the context's own virtual method at vtable offset
 * 132 as the third argument. The result is returned with bit 29 (0x20000000) set; the meaning of
 * that tag is not established, so it is kept as the literal. */
extern "C" {
int FUN_00300db0(...);
int Gap__Core__igPsx2AudioContext__vfunc_55(void **self, int value);
}
/* Stand-in for the context's vtable; vX is the method at vtable offset 132
 * (the number in the class name). */
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
int Gap__Core__igPsx2AudioContext__vfunc_55(void **self, int value) {
    return FUN_00300db0(self, value, ((DW4VC_132_0 *)(self))->vX()) | 0x20000000;
}
