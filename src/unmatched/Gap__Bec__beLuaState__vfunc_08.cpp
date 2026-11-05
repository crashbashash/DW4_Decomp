#include "dw4/reflected.h"
extern "C" {
int Gap__Lua__igLuaState__vfunc_10(beLuaState *);
int Memory_FreeBufferWithAllocator(int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(beLuaState *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beLuaState__vfunc_08(beLuaState *arg0);
}

void Gap__Bec__beLuaState__vfunc_08(beLuaState *arg0) {
    int var_v0;

    if (arg0->_lp != 0) {
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        Memory_FreeBufferWithAllocator(arg0->_lp, var_v0);
    }
    Gap__Lua__igLuaState__vfunc_10(arg0);
}
