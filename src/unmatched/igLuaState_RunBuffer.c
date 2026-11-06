#include "dw4/reflected.h"
int FUN_002467a0();
int lua_dobuffer();
extern int DAT_00498700[4];
extern int DAT_004eaa80[4];
int igLuaState_RunBuffer(igLuaState *arg0, int arg1, int arg2, int arg3) {
    int temp_v0;

    temp_v0 = lua_dobuffer(arg0->_luaState);
    if (temp_v0 != 0) {
        FUN_002467a0(&DAT_004eaa80[0], arg3, DAT_00498700[temp_v0]);
    }
    return temp_v0;
}
