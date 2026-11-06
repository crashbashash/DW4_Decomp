#include "dw4/reflected.h"
/* Vtable slot 34: returns the word at +12 (_luaState, the raw lua_State reference) reinterpreted
 * as float (loaded with lwc1). */
float Gap__Lua__igLuaState__vfunc_34(igLuaState *self) {
    return *(float *)&self->_luaState;
}
