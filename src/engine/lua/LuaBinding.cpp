#include "src/engine/lua/LuaLibrary.h"


int g_luaObjectTag = LUA_UNMADETAG;
int g_luaMetaObjectTag = LUA_UNMADETAG;
int g_luaReservedTag = LUA_UNMADETAG;
/* The tag method each operator class function binds, by LuaFunction's event index. */
const char *g_luaOperatorEvents[] = {"add", "sub", "mul", "div", "pow", "unm", "lt", "ctor"};

igObject *g_luaGluePool;
LuaTagList *g_luaObjectTags;
igLuaGlue::Class *g_luaArrayClasses[LUA_KIND_CHARS + 1];
igLuaGlue::Class *g_luaGlobalClass;
LuaStartupHook *g_luaStartupHooks;
int g_luaClassesAwaitingBase;

#include "src/engine/lua/LuaType.inc"
#include "src/engine/lua/LuaFunction.inc"
#include "src/engine/lua/LuaObject.inc"
#include "src/engine/lua/LuaClass.inc"
#include "src/engine/lua/LuaArray.inc"
#include "src/engine/lua/LuaGlue.inc"
