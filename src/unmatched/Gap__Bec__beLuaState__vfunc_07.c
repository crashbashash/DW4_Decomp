#include "dw4/reflected.h"
int FUN_002446e0();
int FUN_00246130();
int FUN_002464c0();
int lua_baselibopen();
int lua_mathlibopen();
int lua_open();
int lua_strlibopen();
void *Memory_GetAllocatorBySelector();
int igObject_Destroy();
void *igObject_GetAllocator();
extern int DAT_0056df48[4];
extern int DAT_00587098[4];
extern unsigned char GPR_00554be4;
extern unsigned char GPR_00554c14;


void Gap__Bec__beLuaState__vfunc_07(beLuaState *arg0) {
    int temp_s0;
    igObject *temp_a0;
    igObject *var_v0;

    var_v0 = (igObject *)igObject_GetAllocator(arg0);
    var_v0 = (GPR_00554c14 != 0) ? var_v0 : (igObject *)Memory_GetAllocatorBySelector(DAT_00587098[0]);
    if (var_v0 != 0) {
        var_v0->_refCount = (int)var_v0->_refCount + 1;
    }
    temp_a0 = (igObject *)arg0->_memPool;
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int)temp_a0->_refCount - 1;
        if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_memPool = (int)var_v0;
    arg0->_luaState = lua_open(0, arg0->_memPool);
    if (GPR_00554be4 == 0) {
        FUN_002464c0(arg0);
    }
    DAT_0056df48[0] = FUN_00246130(arg0->_luaState);
    temp_s0 = arg0->_luaState;
    lua_baselibopen(temp_s0);
    lua_strlibopen(temp_s0);
    lua_mathlibopen(temp_s0);
    FUN_002446e0(temp_s0);
}
