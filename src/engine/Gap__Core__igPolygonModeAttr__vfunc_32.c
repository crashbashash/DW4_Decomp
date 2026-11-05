/* 0x0013fb70
 * Setter for the attribute's reflected _mode enum field (+0x0c); stores the
 * value as given without validation. */
#include "dw4/reflected.h"
void Gap__Core__igPolygonModeAttr__vfunc_32(igPolygonModeAttr *self, int mode) {
    self->_mode = mode;
}
