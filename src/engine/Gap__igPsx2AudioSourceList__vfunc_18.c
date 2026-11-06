/* Shrinks the list's storage to its element count: when `_count` is below `_capacity`,
 * List_Reserve resizes the buffer to hold `_count` elements of 0x24 (36) bytes each. */
#include "dw4/reflected.h"
int List_Reserve();

void Gap__igPsx2AudioSourceList__vfunc_18(igPsx2AudioSourceList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 0x24);
    }
}
