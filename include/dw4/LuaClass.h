#ifndef DW4_LUACLASS_H
#define DW4_LUACLASS_H
#include "dw4/lua.h"

extern "C" {

void LuaClass_SetOperator(lua_State *L, igLuaGlue::Class *luaClass, LuaFunction *function, int event);
void LuaClass_BindClass(lua_State *L, igLuaGlue::Class *luaClass);
void LuaClassTable_Clear(void);
int LuaClass_GetMember(lua_State *L, igLuaGlue::Class *luaClass, const char *name);
int LuaClass_GetIndexed(lua_State *L, igLuaGlue::Class *luaClass);
int LuaClass_GetTable(lua_State *L);
int LuaClass_SetTable(lua_State *L);
igLuaGlue::Class *LuaClass_FindByName(const char *name);
igLuaGlue::Class *LuaClass_FindByTag(int tag);
igLuaGlue::Class *LuaClass_FindForMeta(igMetaObject *meta);
int LuaClass_DistanceToBase(igLuaGlue::Class *base, igLuaGlue::Class *luaClass);
void LuaClass_SetTagMethod(lua_State *L, igLuaGlue::Class *luaClass, int tag, lua_CFunction handler, const char *event);
void LuaClass_SetTableHandlers(lua_State *L, igLuaGlue::Class *luaClass, int tag, lua_CFunction set, lua_CFunction get);
void LuaClass_Register(igLuaGlue::Class *luaClass, lua_State *L);
void LuaClass_SetBase(igLuaGlue::Class *luaClass, igLuaGlue::Class *base);
int LuaClass_HasTag(igLuaGlue::Class *luaClass, int tag, int *distance);

}

#endif
