#ifndef DW4_LUABINDING_H
#define DW4_LUABINDING_H
#include "dw4/lua.h"

struct LuaTagList;

/* Receives each message LuaError formats, with the data registered alongside. */
typedef void (*LuaErrorHandler)(const char *message, void *data);

extern "C" {

extern LuaTagList *g_luaObjectTags;
extern igLuaGlue::Class *g_luaArrayClasses[LUA_KIND_CHARS + 1];
extern igLuaGlue::Class *g_luaGlobalClass;
extern LuaStartupHook *g_luaStartupHooks;
extern int g_luaClassesAwaitingBase;
extern int g_luaObjectTag;
extern int g_luaMetaObjectTag;
extern int g_luaReservedTag;
extern const char *g_luaOperatorEvents[];
void LuaBinding_SetGlobalUserdata(lua_State *L, const char *name, void *object, int tag);
int LuaBinding_GetGlobal(lua_State *L);
int LuaBinding_SetGlobal(lua_State *L);
int LuaBinding_GetClassTags(lua_State *L);
void *LuaBinding_GetPeer(lua_State *L, int index);
int LuaBinding_New(lua_State *L);
int LuaBinding_Cast(lua_State *L);
void LuaBinding_SetErrorHandler(LuaErrorHandler handler, void *data);
LuaErrorHandler LuaBinding_GetErrorHandler(void **data);

}

#endif
