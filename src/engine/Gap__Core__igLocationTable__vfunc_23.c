/* Number of locations in the table. The locations list stores five ints per location, so the count
 * is the list length divided by five (the resize sibling vfunc_24 sets the length to count * 5). */
#include "dw4/reflected.h"
int Gap__Core__igLocationTable__vfunc_23(igLocationTable *self) {
    return ((igDataList *)(self->_locations))->_count / 5;
}
