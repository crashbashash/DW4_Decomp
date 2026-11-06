/* Map a hash value to a bucket of the tracker's hash index: the value modulo the count stored at
 * +8 of the `_hashIndex` object, or 0 while that count is 0. */
#include "dw4/reflected.h"
unsigned int Gap__Core__igEventTracker__vfunc_48(igEventTracker *self, unsigned int hash) {
    unsigned int bucketCount;

    bucketCount = *(int *)((char *)(self->_hashIndex) + 8);
    if (bucketCount != 0) {
        return hash % bucketCount;
    }
    return 0U;
}
