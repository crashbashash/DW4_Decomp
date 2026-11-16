#ifndef DW4_LUAOBJECT_H
#define DW4_LUAOBJECT_H
#include "dw4/lua.h"

class LuaBoundObject;

extern "C" {

bool LuaObject_PushField(lua_State *L, igMetaField *field, LuaBoundObject *object);
int LuaObject_StoreField(lua_State *L, igMetaField *field, LuaBoundObject *object, int index);
int LuaObject_New(lua_State *L);
const char *LuaMetaField_GetName(igMetaField *field);
unsigned int LuaFieldTable_Key(igMetaObject *meta, const char *name);
int LuaObject_Collect(lua_State *L);
int LuaObject_GetTable(lua_State *L);
int LuaObject_SetTable(lua_State *L);
int LuaPeer_GetTable(lua_State *L);
void LuaPeer_NoteSetError(const char *message, void *data);
int LuaPeer_SetTable(lua_State *L);
void LuaObject_SetField(lua_State *L, igMetaField *field, LuaBoundObject *object, const char *key, int index);

}

#endif
