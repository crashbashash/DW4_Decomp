#include "dw4/reflected.h"
int FUN_002467a0();
int lua_dofile();
extern int DAT_00498700[4];
extern int DAT_004eaa50[4];
int igLuaState_RunFile(igLuaState *arg0, int arg1) {
    int temp_v0;

    temp_v0 = lua_dofile(arg0->_luaState);
    if (temp_v0 != 0) {
        FUN_002467a0(&DAT_004eaa50[0], arg1, DAT_00498700[temp_v0]);
    }
    return temp_v0;
}
