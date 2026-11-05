/* 0x0013f840 igMultiPassStateAttr vtable slot 32: field-store leaf.  Stores its argument
 * into the reflected `_numPasses` field (+12, igIntMetaField in include/dw4/reflected.h),
 * so it acts as the pass-count setter of the attribute. */
#include "dw4/reflected.h"
void Gap__Core__igMultiPassStateAttr__vfunc_32(igMultiPassStateAttr *self, int numPasses) {
    self->_numPasses = numPasses;
}
