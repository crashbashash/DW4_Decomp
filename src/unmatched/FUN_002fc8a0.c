#include "dw4/reflected.h"
int FUN_002fc8a0(igMetaField *arg0) {
    if (arg0->_persistent == 0 || arg0->_isRunTime != 0) {
        return 0;
    }
    return (arg0->_size + 3) & ~3;
}
