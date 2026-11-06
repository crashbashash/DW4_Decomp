#include "dw4/reflected.h"

/* Predicate: true when the struct field metadata has a C++ constructor hook (`_cppConstructor`,
 * igRawRefMetaField, +56) set. */
int Gap__Core__igStructMetaField__vfunc_60(igStructMetaField *self) {
    return self->_cppConstructor != 0;
}
