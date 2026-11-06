/* Trim the list's storage down to its used length: when `_count` is below `_capacity`,
 * List_Reserve re-sizes the buffer to `_count` elements of 0x28 bytes. Same shape as
 * igIntList_TrimCapacity (element size 4) and igObjectList_TrimCapacity. */
#include "dw4/reflected.h"
int List_Reserve();

void Gap__Gui__igCharMetricsList__vfunc_18(igCharMetricsList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 0x28);
    }
}
