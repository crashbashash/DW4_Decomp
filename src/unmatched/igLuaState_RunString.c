#include "dw4/reflected.h"
int FUN_002467a0();
int lua_dostring();
extern int DAT_00498700[4];
extern int DAT_004eaa20[4];
int igLuaState_RunString(igLuaState *arg0) {
    int temp_v0;
    temp_v0 = lua_dostring(arg0->_luaState);
    if (temp_v0 != 0) {
        FUN_002467a0(&DAT_004eaa20[0], DAT_00498700[temp_v0]);
    }
    return temp_v0;
}
