/* Hash-bucket index for `key`: key modulo the hash-table size (`_hashCapacity`), or 0 when there
 * is none. */
#include "dw4/reflected.h"
unsigned int Gap__Core__igLocationTable__vfunc_30(igLocationTable *self, unsigned int key) {
    unsigned int hash_capacity;

    hash_capacity = self->_hashCapacity;
    if (hash_capacity != 0) {
        return key % hash_capacity;
    }
    return 0U;
}
