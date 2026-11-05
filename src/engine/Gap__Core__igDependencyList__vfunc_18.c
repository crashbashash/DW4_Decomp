/* 0x00331e80
 * Trim the list's storage down to its used length: when `_count` is below
 * `_capacity`, List_Reserve re-sizes the buffer to `_count` elements of 8 bytes.
 * Same shape as igIntList_TrimCapacity (element size 4) and igObjectList_TrimCapacity. */
#include "dw4/reflected.h"
int List_Reserve();

void Gap__Core__igDependencyList__vfunc_18(igDependencyList *self) {
    int count;

    count = self->_count;
    if (count < self->_capacity) {
        List_Reserve(self, count, 8);
    }
}
