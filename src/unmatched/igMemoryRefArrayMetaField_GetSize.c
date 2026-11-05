/* 0x002fa8b0 — igMemoryRefArrayMetaField_GetSize. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
#include "dw4/reflected.h"
int igMemoryRefArrayMetaField_GetSize(igMemoryRefArrayMetaField *arg0) {
    return (arg0->_num * 4) & 0xFFFF;
}
