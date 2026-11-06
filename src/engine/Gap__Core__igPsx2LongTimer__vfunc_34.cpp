/* Preset time in seconds. Reads the preset through the virtual at slot 35 (returns _resetTime, a
 * nanosecond count) and converts it to a double: whole seconds plus the leftover nanoseconds
 * divided by 1e9, with the soft-float helpers the EE needs for doubles. Its setter twin is
 * vfunc_32. */
extern "C" {
int __divdi3(...);
int __moddi3(...);
int __floatdidf(...);
int __adddf3(...);
int __divdf3(...);
int __floatsidf(...);
void Gap__Core__igPsx2LongTimer__vfunc_34(void **self);
}
/* matching construct: dummy-virtual class so the call below compiles to retail's slot-35 vtable call */
class DW4VC_140_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(); };
#define NANOSECONDS_PER_SECOND 0x3B9ACA00 /* 1e9 */
void Gap__Core__igPsx2LongTimer__vfunc_34(void **self) {
    int remainderNsAsDouble; /* the EE soft-float helpers pass doubles as integer register pairs */
    int fractionSeconds;
    int presetNs;

    presetNs = ((DW4VC_140_0 *)(self))->vX();
    remainderNsAsDouble = __floatdidf(__moddi3(presetNs, NANOSECONDS_PER_SECOND));
    fractionSeconds = __divdf3(remainderNsAsDouble, __floatsidf(NANOSECONDS_PER_SECOND));
    __adddf3(__floatdidf(__divdi3(presetNs, NANOSECONDS_PER_SECOND)), fractionSeconds);
}
