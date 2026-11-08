/* Sets the preset time from seconds. Converts a double count of seconds to the timer's nanosecond
 * unit (seconds * 1e9, truncated to a 64-bit integer) and stores it through the virtual at slot 33
 * (writes _resetTime). Setter twin of vfunc_34, which reads the preset back as seconds. The EE has
 * no double hardware, so the arithmetic goes through the soft-float runtime and the double travels
 * as an integer register pair. */
extern "C" {
int __fixdfdi(...);
int dpmul(...);
int litodp(...);
void Gap__Core__igPsx2LongTimer__vfunc_32(void **self, int seconds_as_double);
}
/* matching construct: dummy-virtual class so the call below compiles to retail's slot-33 vtable call */
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
#define NANOSECONDS_PER_SECOND 0x3B9ACA00 /* 1e9, as in vfunc_34 */
void Gap__Core__igPsx2LongTimer__vfunc_32(void **self, int seconds_as_double) {
    ((DW4VC_132_1 *)(self))->vX((int)(__fixdfdi(dpmul(litodp(NANOSECONDS_PER_SECOND), seconds_as_double))));
}
