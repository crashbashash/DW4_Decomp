/* 0x002ee520 igMemoryDictionary vtable slot 24: field-store leaf.  Stores its argument into
 * the reflected `_capacity` field (+8, igIntMetaField in include/dw4/reflected.h), so it
 * acts as the capacity setter of the dictionary. */
#include "dw4/reflected.h"
void Gap__Core__igMemoryDictionary__vfunc_24(igMemoryDictionary *self, int capacity) {
    self->_capacity = capacity;
}
