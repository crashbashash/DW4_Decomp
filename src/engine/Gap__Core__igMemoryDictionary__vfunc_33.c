/* Hash-bucket index for `key`: key modulo the table capacity (`_capacity`), or 0 for an empty
 * table. */
#include "dw4/reflected.h"
unsigned int Gap__Core__igMemoryDictionary__vfunc_33(igMemoryDictionary *self, unsigned int key) {
    unsigned int capacity;

    capacity = self->_capacity;
    if (capacity != 0) {
        return key % capacity;
    }
    return 0U;
}
