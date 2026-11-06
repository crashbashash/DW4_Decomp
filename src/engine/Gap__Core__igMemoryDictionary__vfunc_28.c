/* Predicate: true once the dictionary has storage allocated, i.e. its `_capacity` (+8) is non-
 * zero. */
#include "dw4/reflected.h"
int Gap__Core__igMemoryDictionary__vfunc_28(igMemoryDictionary *self) {
    return self->_capacity != 0;
}
