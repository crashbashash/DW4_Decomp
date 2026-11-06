#include "dw4/reflected.h"
int igMemoryRefArrayMetaField_GetSize(igMemoryRefArrayMetaField *arg0) {
    return (arg0->_num * 4) & 0xFFFF;
}
