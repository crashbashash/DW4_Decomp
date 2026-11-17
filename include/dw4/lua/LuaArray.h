#ifndef DW4_LUAARRAY_H
#define DW4_LUAARRAY_H
#include "dw4/lua/lua.h"

extern "C" {

int LuaCharArray_Delete(lua_State *L);
int LuaCharArray_Get(lua_State *L);
int LuaCharArray_Set(lua_State *L);
int LuaCharArray_New(lua_State *L);
int LuaUnsignedCharArray_Delete(lua_State *L);
int LuaUnsignedCharArray_Get(lua_State *L);
int LuaUnsignedCharArray_Set(lua_State *L);
int LuaUnsignedCharArray_New(lua_State *L);
int LuaShortArray_Delete(lua_State *L);
int LuaShortArray_Get(lua_State *L);
int LuaShortArray_Set(lua_State *L);
int LuaShortArray_New(lua_State *L);
int LuaUnsignedShortArray_Delete(lua_State *L);
int LuaUnsignedShortArray_Get(lua_State *L);
int LuaUnsignedShortArray_Set(lua_State *L);
int LuaUnsignedShortArray_New(lua_State *L);
int LuaIntArray_Delete(lua_State *L);
int LuaIntArray_Get(lua_State *L);
int LuaIntArray_Set(lua_State *L);
int LuaIntArray_New(lua_State *L);
int LuaUnsignedIntArray_Delete(lua_State *L);
int LuaUnsignedIntArray_Get(lua_State *L);
int LuaUnsignedIntArray_Set(lua_State *L);
int LuaUnsignedIntArray_New(lua_State *L);
int LuaLongArray_Delete(lua_State *L);
int LuaLongArray_Get(lua_State *L);
int LuaLongArray_Set(lua_State *L);
int LuaLongArray_New(lua_State *L);
int LuaUnsignedLongArray_Delete(lua_State *L);
int LuaUnsignedLongArray_Get(lua_State *L);
int LuaUnsignedLongArray_Set(lua_State *L);
int LuaUnsignedLongArray_New(lua_State *L);
int LuaBoolArray_Delete(lua_State *L);
int LuaBoolArray_Get(lua_State *L);
int LuaBoolArray_Set(lua_State *L);
int LuaBoolArray_New(lua_State *L);
int LuaFloatArray_Delete(lua_State *L);
int LuaFloatArray_Get(lua_State *L);
int LuaFloatArray_Set(lua_State *L);
int LuaFloatArray_New(lua_State *L);
int LuaDoubleArray_Delete(lua_State *L);
int LuaDoubleArray_Get(lua_State *L);
int LuaDoubleArray_Set(lua_State *L);
int LuaDoubleArray_New(lua_State *L);

}

#endif
