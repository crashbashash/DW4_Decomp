/* 0x00303a40 - Gap__Core__igObjectRefMetaField__vfunc_42. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
#include "dw4/reflected.h"
int igObject_VisitFields();

void Gap__Core__igObjectRefMetaField__vfunc_42(igObjectRefMetaField *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;

    temp_a0 = *(int *)(arg1 + arg0->_offset);
    if (temp_a0 != 0) {
        igObject_VisitFields(temp_a0, arg2, arg3);
    }
}
