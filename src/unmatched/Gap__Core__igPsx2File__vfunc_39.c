#include "dw4/reflected.h"
int FUN_0010f738();

int Gap__Core__igPsx2File__vfunc_39(igPsx2File *arg0) {
    if (arg0->_isBinary != 0) {
        return FUN_0010f738(arg0->_fileHandle, 0, 1);
    }
    return arg0->_bufPos;
}
