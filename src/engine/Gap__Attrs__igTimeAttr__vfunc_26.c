/* Take the 64-bit time stored at +96 of `source` (an object not typed in reflected.h) as this
 * attribute's `_time`. */
#include "dw4/reflected.h"
void Gap__Attrs__igTimeAttr__vfunc_26(igTimeAttr *self, void *source) {
    self->_time = (long long) *(long long *)((char *)(source) + 96);
}
