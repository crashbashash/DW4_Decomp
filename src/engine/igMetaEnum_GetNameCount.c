/* Number of names in the enum: the `_count` of its `_names` list (a list with the igDataList
 * header: _count +8, _capacity +12, _data +16). */
#include "dw4/reflected.h"
int igMetaEnum_GetNameCount(igMetaEnum *self) {
    return ((igDataList *)self->_names)->_count;
}
