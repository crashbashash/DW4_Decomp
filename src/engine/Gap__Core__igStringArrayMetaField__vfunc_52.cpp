/* 0x0030a560
 * igStringArrayMetaField slot 52: forwards (item, count * _num) to slot 50 of the
 * element type's default descriptor, so an array field of _num elements covers
 * _num times the requested count.  The descriptor is the lazily created object
 * cached at 0x00585910 (the cell sits between the igStringMetaField and
 * igStringArrayMetaField class handles, the same layout as the confirmed
 * default-descriptor getters). */
#include "dw4/reflected.h"
extern "C" {
void **FUN_002b9c60(...);  /* igStringMetaField default-descriptor getter (name inferred, not confirmed) */
void Gap__Core__igStringArrayMetaField__vfunc_52(igStringArrayMetaField *self, int item, int count);
}
/* Placeholder vtable: only the call through slot 50 of the descriptor is used. */
class DW4VC_208_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
void Gap__Core__igStringArrayMetaField__vfunc_52(igStringArrayMetaField *self, int item, int count) {
    void **descriptor;

    descriptor = (void **)(FUN_002b9c60());
    ((DW4VC_208_2 *)(descriptor))->vX((int)(item), (int)(count * self->_num));
}
