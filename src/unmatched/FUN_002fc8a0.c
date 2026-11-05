/* 0x002fc8a0 - FUN_002fc8a0. single || condition early return 0 (retail has two zero-return arms) Verified byte-identical by tools/verify.py. */
#include "dw4/reflected.h"
int FUN_002fc8a0(igMetaField *arg0) {
    if (arg0->_persistent == 0 || arg0->_isRunTime != 0) {
        return 0;
    }
    return (arg0->_size + 3) & ~3;
}
