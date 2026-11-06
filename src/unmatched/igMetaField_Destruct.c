#include "dw4/reflected.h"
int igObject_FreeStorage();
int Gap__Core__igObject__vfunc_00__002ff0a0();

void igMetaField_Destruct(igMetaField *arg0) {
    int temp_a1;

    temp_a1 = arg0->_default;
    if (temp_a1 != 0) {
        igObject_FreeStorage(arg0, temp_a1);
    }
    Gap__Core__igObject__vfunc_00__002ff0a0(arg0);
}
