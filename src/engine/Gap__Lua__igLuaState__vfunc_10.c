/* 0x002465f0
 * Shutdown step of igLuaState: lua_close takes the raw Lua state
 * (`_luaState`), then FUN_00246230 is run on the global that
 * Gap::Bec::beLuaState::vfunc_07 (the init counterpart) fills with the result
 * of FUN_00246130(_luaState) at 0x0056df48.  What the two callees do is not
 * established. */
#include "dw4/reflected.h"
int FUN_00246230(int);
int lua_close(int);
extern int g_luaInitResult_0056df48[4];

void Gap__Lua__igLuaState__vfunc_10(igLuaState *self) {
    lua_close(self->_luaState);
    FUN_00246230(g_luaInitResult_0056df48[0]);
}
