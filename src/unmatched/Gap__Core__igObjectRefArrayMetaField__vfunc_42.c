#include "dw4/reflected.h"
int igObject_VisitFields();

void Gap__Core__igObjectRefArrayMetaField__vfunc_42(igObjectRefArrayMetaField *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;
    int var_s0;

    for (var_s0 = 0; var_s0 < arg0->_num; var_s0++) {
        temp_a0 = *(int *)(arg1 + arg0->_offset + (var_s0 * 4));
        if (temp_a0 != 0) {
            igObject_VisitFields(temp_a0, arg2, arg3);
        }
    }
}
