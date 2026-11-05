/* 0x0013c180
 * Shrink the object-pointer list's storage to its element count: when `_count` is below
 * `_capacity`, List_Reserve (0x002d6680) resizes the buffer to hold `_count`
 * elements of 4 bytes each. */
#include "dw4/reflected.h"
int List_Reserve();

void igObjectList_TrimCapacity(igObjectList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 4);
    }
}
