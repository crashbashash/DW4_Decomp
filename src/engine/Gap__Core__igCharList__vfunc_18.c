#include "dw4/reflected.h"
int List_Reserve();

void Gap__Core__igCharList__vfunc_18(igCharList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 1);
    }
}
