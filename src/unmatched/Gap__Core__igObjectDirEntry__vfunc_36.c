#include "dw4/reflected.h"
int igObject_RegisterInstance();

void Gap__Core__igObjectDirEntry__vfunc_36(igObjectDirEntry *arg0, int arg1) {
    int temp_a0;

    temp_a0 = arg0->_ref;
    if (temp_a0 != 0) {
        if (arg1 != 0) {
            igObject_RegisterInstance(temp_a0, arg0->_typeMeta);
            return;
        }
        igObject_RegisterInstance(temp_a0, 0);
    }
}
