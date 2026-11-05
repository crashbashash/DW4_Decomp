#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(beLuaDataObject *);
int Memory_FreeBuffer(int);
void Gap__Bec__beLuaDataObject__vfunc_08(beLuaDataObject *arg0);
}

void Gap__Bec__beLuaDataObject__vfunc_08(beLuaDataObject *arg0) {
    int temp_a0;

    temp_a0 = arg0->_data;
    if (temp_a0 != 0) {
        Memory_FreeBuffer(temp_a0);
    }
    arg0->_data = 0;
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
