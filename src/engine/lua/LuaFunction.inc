LuaFunction::LuaFunction(lua_CFunction function, int id, const char *name, const LuaType &result,
                         igLuaGlue::Class *owner, int isMethod, int argCount) {
    link.key = (unsigned int)owner ^ LuaBinding_HashName(name);
    link.next = 0;
    link.prev = 0;
    LuaFunctionTable_Insert(&link);
    this->name = name;
    this->result = result;
    this->owner = owner;
    this->function = function;
    nextOverload = 0;
    this->id = id;
    this->argCount = argCount;
    hasSelf = result.kind != LUA_KIND_STATIC && owner->name[0] != 0;
    isUnique = 1;
    hasOutArgs = 0;
    this->isMethod = isMethod;
}

/* Converts the arguments, calls the C++ function with them as userdata on top of the stack and
 * stores the arguments it changed back into the tables they came from. */
int LuaFunction_Call(LuaFunction *function, lua_State *L) {
    int argCount;
    LuaValue storage[64];
    LuaValue *values;
    LuaType *argTypes;
    int first;
    int i;
    void *peer;
    int result;

    argCount = function->argCount;
    if (function->isMethod != 0) {
        peer = LuaBinding_GetPeer(L, 1);
        if (peer != 0) {
            lua_pushusertag(L, peer, lua_tag(L, 1));
            lua_insert(L, 1);
            lua_remove(L, 2);
        }
    }
    if (argCount == 0) {
        return function->function(L);
    }
    values = storage;
    argTypes = (LuaType *)(function + 1);
    first = function->hasSelf ? 2 : 1;
    for (i = 0; i < argCount; i++) {
        new (&values[i]) LuaValue(&argTypes[i], L, first + i);
    }
    lua_pushusertag(L, values, 0);
    lua_insert(L, -2);
    result = function->function(L);
    if (function->hasOutArgs != 0) {
        for (i = 0; i < argCount; i++) {
            if (values[i].type.writeBack != 0) {
                LuaValue_StoreInTable(&values[i], L, first + i);
            }
        }
    }
    return result;
}

/* Binds an operator to a class and every class derived from it. */
void LuaClass_SetOperator(lua_State *L, igLuaGlue::Class *luaClass, LuaFunction *function, int event) {
    const char **eventName;
    igLuaGlue::Class *derived;

    lua_pushusertag(L, function, 0);
    lua_pushcclosure(L, LuaFunction_CallOperator, 1);
    lua_pushvalue(L, -1);
    eventName = &g_luaOperatorEvents[event];
    lua_settagmethod(L, luaClass->instanceTag, *eventName);
    lua_settagmethod(L, luaClass->referenceTag, *eventName);
    for (derived = luaClass->firstDerived; derived != 0; derived = derived->nextSibling) {
        LuaClass_SetOperator(L, derived, function, event);
    }
}

/* Stores a function in the table on top of the stack under the key below it. */
void LuaFunction_SetField(lua_State *L, LuaFunction *function) {
    lua_pushusertag(L, function, 0);
    if (function->isUnique == 0) {
        lua_pushcclosure(L, LuaFunction_CallOverload, 1);
    } else if (!function->argCount) {
        lua_pushcclosure(L, function->function, 1);
    } else {
        lua_pushcclosure(L, LuaFunction_CallUpvalue, 1);
    }
    lua_rawset(L, -3);
}

/* Binds a class's functions from the tables a binding generator writes: one code word per
 * function (id, argument count, name index, method flag and whether the method entry point
 * handles it) followed by the result's and each argument's type code. */
void LuaClass_BindFunctions(igLuaGlue::Class *owner, lua_CFunction method, lua_CFunction function,
                            const char **names, int count, const unsigned int *codes, LuaFunction **byId) {
    int i;
    unsigned int code;
    unsigned int argCount;
    LuaFunction *bound;
    LuaType *argTypes;
    unsigned int j;

    for (i = 0; i < count; i++) {
        code = *codes++;
        argCount = (code >> 8) & 31;
        bound = new (Memory_AllocateBufferDirect(argCount * sizeof(LuaType) + sizeof(LuaFunction), g_luaGluePool))
            LuaFunction(((code >> 30) & 1) ? method : function, code & 0xff, names[(code >> 13) & 0x1ffff],
                        LuaType(names, *codes++), owner, ((code >> 31) & 1) != 0, argCount);
        if (byId != 0 && bound->isMethod) byId[bound->id] = bound;
        argTypes = (LuaType *)(bound + 1);
        for (j = 0; j < argCount; j++) {
            new (&argTypes[j]) LuaType(names, *codes++);
        }
    }
}

/* The `getglobal` tag method: a global function of the bound classes, else a meta-object of
 * that name, which becomes a global. */
int LuaBinding_GetGlobal(lua_State *L) {
    const char *name;
    igMetaObject *meta;

    name = lua_tostring(L, 1);
    if (g_luaGlobalClass != 0) {
        lua_insert(L, 1);
        lua_pushusertag(L, g_luaGlobalClass, 0);
        return LuaClass_GetTable(L);
    }
    meta = igObjectSystem_FindMetaByNameDefault(name);
    if (meta != 0) {
        LuaBinding_SetGlobalUserdata(L, name, meta, g_luaMetaObjectTag);
        lua_settop(L, 0);
        lua_pushusertag(L, meta, g_luaMetaObjectTag);
        return 1;
    }
    return 0;
}

/* The `setglobal` tag method: a global variable of the bound classes, else a plain global. */
int LuaBinding_SetGlobal(lua_State *L) {
    LuaProperty *property;

    if (g_luaGlobalClass != 0) {
        property = LuaPropertyTable_Find(g_luaGlobalClass, lua_tostring(L, 1));
        if (property != 0) {
            lua_pushusertag(L, property, 0);
            return property->owner->setHandler(L);
        }
    }
    lua_getglobals(L);
    lua_pushvalue(L, 1);
    lua_pushvalue(L, 3);
    lua_rawset(L, -3);
    return 0;
}
