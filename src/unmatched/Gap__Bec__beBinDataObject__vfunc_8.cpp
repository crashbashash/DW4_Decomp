#include "dw4/reflected.h"
extern "C" {
int Memory_FreeBuffer(void *);
int Gap__Core__igObject__vfunc_08__002ff0f0(void *);
void Gap__Bec__beBinDataObject__vfunc_8(beBinDataObject *arg0);
}

void Gap__Bec__beBinDataObject__vfunc_8(beBinDataObject *arg0) {
    if (arg0->_dataBuffer != 0) {
        Memory_FreeBuffer((void *)arg0->_dataBuffer);
        arg0->_dataBuffer = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
