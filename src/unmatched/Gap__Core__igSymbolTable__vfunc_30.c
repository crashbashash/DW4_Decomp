#include "dw4/reflected.h"
unsigned int Gap__Core__igSymbolTable__vfunc_30(igSymbolTable *arg0, int arg1) {
    unsigned int temp_a2;
    unsigned int temp_v1;
    unsigned int var_v0;

    temp_a2 = arg0->_hashCapacity;
    var_v0 = 0;
    if (temp_a2 != 0) {
        temp_v1 = arg0->_hashIncrement;
        if (temp_v1 != 0) {
            var_v0 = (int)((unsigned int) ((unsigned int) (arg1 - arg0->_lowAddress) / temp_v1) % temp_a2);
        }
    }
    return var_v0;
}
