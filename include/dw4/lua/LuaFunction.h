#ifndef DW4_LUAFUNCTION_H
#define DW4_LUAFUNCTION_H
#include "dw4/lua/lua.h"

struct LuaProperty;
struct LuaConstant;

extern "C" {

LuaFunction *LuaFunctionTable_Find(igLuaGlue::Class *owner, const char *name, bool callback);
void LuaFunctionTable_BindAll(lua_State *L);
LuaFunction *LuaFunction_Resolve(LuaFunction *function, lua_State *L, int first, int last);
void LuaFunctionTable_LinkOverloads(void);
int LuaFunction_Call(LuaFunction *function, lua_State *L);
void LuaFunction_SetField(lua_State *L, LuaFunction *function);
void LuaFunctionTable_Clear(void);
LuaProperty *LuaPropertyTable_Find(igLuaGlue::Class *owner, const char *name);
void LuaPropertyTable_Clear(void);
LuaConstant *LuaConstantTable_Find(const char *name, igLuaGlue::Class *owner);
void LuaConstantTable_Clear(void);
void LuaEnumTable_Clear(void);
int LuaFunction_CallMember(lua_State *L);
int LuaFunction_CallUpvalue(lua_State *L);
int LuaFunction_CallOverload(lua_State *L);
int LuaFunction_CallOperator(lua_State *L);
int LuaFunction_CallUnaryOperator(lua_State *L);

}

#endif
