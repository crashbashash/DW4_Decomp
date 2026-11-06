#include "dw4/reflected.h"

/* Setter: stores the alpha-test reference value (`_refValue`, an igFloatMetaField of the reflected
 * igAlphaFunctionAttr). */
void Gap__Attrs__igAlphaFunctionAttr__vfunc_33(igAlphaFunctionAttr *self, float refValue) {
    self->_refValue = refValue;
}
