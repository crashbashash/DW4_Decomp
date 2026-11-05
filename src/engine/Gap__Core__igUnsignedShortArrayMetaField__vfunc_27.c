#include "dw4/reflected.h"

/* 0x0030eea0
 * igUnsignedShortArrayMetaField vtable slot 27 (+0x6c): constant leaf returning 2, the byte size of one
 * unsigned short element.  The same igMetaField slot is the base's `return -1` and igStructMetaField's
 * `_alignment` accessor (Gap__Core__igStructMetaField__vfunc_27); its role is not pinned (finding #365). */
int Gap__Core__igUnsignedShortArrayMetaField__vfunc_27(igUnsignedShortArrayMetaField *self) {
    return 2;
}
