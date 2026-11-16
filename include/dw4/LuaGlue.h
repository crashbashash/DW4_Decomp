#ifndef DW4_LUAGLUE_H
#define DW4_LUAGLUE_H
#include "dw4/lua.h"

extern "C" {

void LuaGlue_Initialize(void);
void LuaGlue_Shutdown(void);
void LuaGlue_OpenLibrary(lua_State *L);

}

#endif
