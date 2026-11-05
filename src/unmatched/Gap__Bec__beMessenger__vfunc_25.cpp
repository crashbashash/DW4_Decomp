#include "dw4/reflected.h"
extern "C" {
int beMessenger_InitializeMemory();
int Gap__Bec__beMessenger__vfunc_25(beMessenger *arg0);
}

int Gap__Bec__beMessenger__vfunc_25(beMessenger *arg0) {
    if (arg0->_isMemoryAssign == 0) {
        beMessenger_InitializeMemory();
    }
    return 0;
}
