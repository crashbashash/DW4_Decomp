#include "dw4/reflected.h"
int memcpy();
void FUN_002fc9f0(igMetaField *arg0, int arg1, int arg2) {
    memcpy(arg1 + arg0->_offset, arg2 + arg0->_offset, arg0->_size);
}
