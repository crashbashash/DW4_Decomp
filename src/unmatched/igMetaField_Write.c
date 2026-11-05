/* 0x002fcea0 — igMetaField_Write. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igMetaField_Write(igMetaField *arg0) {
    return -(arg0->_persistent == 0);
}
