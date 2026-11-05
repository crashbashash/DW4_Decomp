#include "dw4/reflected.h"

/* 0x0030ec40
 * igUnsignedLongArrayMetaField vtable slot 27 (+0x6c): constant leaf returning 8, the byte size of one
 * unsigned long element (a 64-bit value on this target).  The same igMetaField slot is the base's
 * `return -1` and igStructMetaField's `_alignment` accessor (Gap__Core__igStructMetaField__vfunc_27);
 * its role is not pinned (finding #365). */
int Gap__Core__igUnsignedLongArrayMetaField__vfunc_27(igUnsignedLongArrayMetaField *self) {
    return 8;
}
