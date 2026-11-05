#include "dw4/reflected.h"
extern "C" {
igObject *FUN_0035aa20(int);
int Memory_GetAllocatorBySelector(int);
void igObject_Destroy(igObject *);
int igObject_GetAllocator(beLua *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_0038a2d0(beLua *arg0);
}

void FUN_0038a2d0(beLua *arg0) {
    int var_v0;
    int alloc;
    igObject *temp_a0;

    alloc = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = alloc;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    temp_a0 = (igObject *)arg0->_luaState;
    if (temp_a0 != 0) {
        --temp_a0->_refCount;
        if (((unsigned long long)(long long)temp_a0->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_luaState = (int)FUN_0035aa20(var_v0);
}
