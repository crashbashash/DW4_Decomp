#include "dw4/reflected.h"

/* 0x0013b770
 * Setter: stores the alpha-test reference value (`_refValue`, an
 * igFloatMetaField of the reflected igAlphaFunctionAttr). */
void Gap__Core__igAlphaFunctionAttr__vfunc_33(igAlphaFunctionAttr *self, float refValue) {
    self->_refValue = refValue;
}
