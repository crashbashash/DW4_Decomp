#ifndef DW4_LUATYPE_H
#define DW4_LUATYPE_H
#include "dw4/lua/lua.h"

class LuaBoundObject;

extern "C" {

void LuaType_UpdateAccepted(LuaType *type);
int LuaType_IsNumber(LuaType *type);
int LuaType_MatchesUserdata(LuaType *type, int tag, LuaBoundObject *object, int *distance);
void LuaType_PushObject(LuaType *type, lua_State *L, LuaBoundObject *object, int mode);
void LuaType_PushPointer(LuaType *type, lua_State *L, int mode, LuaBoundObject *object);
int LuaType_Accepts(LuaType *type, lua_State *L, int index, int *distance);
void LuaValue_StoreInTable(LuaValue *value, lua_State *L, int table);

}

#endif
