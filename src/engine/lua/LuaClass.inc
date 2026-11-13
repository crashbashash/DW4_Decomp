/* The Lua class of a meta-object or of its nearest ancestor that has one. */
LuaClass *LuaClass_FindForMeta(igMetaObject *meta) {
    igMetaObject *m;
    LuaClass *luaClass;

    for (m = meta; m != 0; m = (igMetaObject *)m->_parent) {
        luaClass = LuaClass_FindByName((const char *)m->_name);
        if (luaClass != 0) return luaClass;
    }
    return 0;
}

/* How many derivations lead from `luaClass` up to `base`, -1 when it does not derive from it. */
int LuaClass_DistanceToBase(LuaClass *base, LuaClass *luaClass) {
    int distance = 0;
    while (luaClass != 0) {
        if (luaClass == base) {
            return distance;
        }
        luaClass = luaClass->base;
        distance++;
    }
    return -1;
}

void LuaClass_SetTagMethod(lua_State *L, LuaClass *luaClass, int tag, lua_CFunction handler, const char *event) {
    lua_pushusertag(L, luaClass, 0);
    lua_pushcclosure(L, handler, 1);
    lua_settagmethod(L, tag, event);
}

void LuaClass_SetTableHandlers(lua_State *L, LuaClass *luaClass, int tag, lua_CFunction set, lua_CFunction get) {
    LuaClass_SetTagMethod(L, luaClass, tag, set, "settable");
    LuaClass_SetTagMethod(L, luaClass, tag, get, "gettable");
}

/* Gives a class its tags, its global class table and its tag methods. A class with a
 * constructor handles its instances itself; one with a meta-object reads and writes the
 * reflected fields; the others go through their class tables. */
void LuaClass_Register(LuaClass *luaClass, lua_State *L) {
    char *peerName;
    int tag;

    luaClass->classTag = lua_newtag(L);
    LuaBinding_SetGlobalUserdata(L, luaClass->name, luaClass, luaClass->classTag);
    if (luaClass->peerConstructor != 0) {
        peerName = new char[strlen(luaClass->name) + 5];
        sprintf(peerName, "%sPeer", luaClass->name);
        lua_getglobals(L);
        lua_pushstring(L, peerName);
        lua_pushcclosure(L, luaClass->peerConstructor, 0);
        lua_rawset(L, -3);
        lua_settop(L, -2);
        delete[] peerName;
    }
    if (luaClass->constructor != 0) {
        LuaClass_SetTagMethod(L, luaClass, luaClass->classTag, luaClass->constructor, "function");
        luaClass->instanceTag = lua_newtag(L);
        lua_pushcclosure(L, luaClass->gcHandler, 0);
        lua_settagmethod(L, luaClass->instanceTag, "gc");
        luaClass->referenceTag = lua_newtag(L);
        LuaClass_SetTableHandlers(L, luaClass, luaClass->instanceTag, luaClass->setHandler, luaClass->getHandler);
        LuaClass_SetTableHandlers(L, luaClass, luaClass->referenceTag, luaClass->setHandler, luaClass->getHandler);
        return;
    }
    if (luaClass->metaObject != 0) {
        tag = lua_newtag(L);
        luaClass->referenceTag = tag;
        luaClass->instanceTag = tag;
        if (g_luaObjectTags->indexOf(luaClass->instanceTag) < 0) {
            g_luaObjectTags->insertSorted(&luaClass->instanceTag);
        }
        LuaClass_SetTagMethod(L, luaClass, luaClass->instanceTag, LuaObject_Collect, "gc");
        LuaClass_SetTableHandlers(L, luaClass, luaClass->instanceTag, LuaObject_SetTable, LuaObject_GetTable);
        LuaClass_SetTagMethod(L, luaClass, luaClass->classTag, LuaObject_New, "function");
    } else {
        luaClass->instanceTag = lua_newtag(L);
        luaClass->referenceTag = lua_newtag(L);
        if (luaClass->gcHandler != 0) {
            LuaClass_SetTagMethod(L, luaClass, luaClass->instanceTag, luaClass->gcHandler, "gc");
        }
        LuaClass_SetTableHandlers(L, luaClass, luaClass->instanceTag, LuaClass_SetTable, LuaClass_GetTable);
        LuaClass_SetTableHandlers(L, luaClass, luaClass->referenceTag, LuaClass_SetTable, LuaClass_GetTable);
    }
    lua_newtable(L);
    lua_settag(L, luaClass->classTag);
    lua_pushvalue(L, -1);
    luaClass->classTableRef = lua_ref(L, -1);
    LuaClass_SetTableHandlers(L, luaClass, luaClass->classTag, LuaClass_SetTable, LuaClass_GetTable);
}

void LuaClass_SetBase(LuaClass *luaClass, LuaClass *base) {
    if (base != 0) {
        luaClass->nextSibling = base->firstDerived;
        if (luaClass->nextSibling != 0) {
            luaClass->nextSibling->prevSibling = luaClass;
        }
        base->firstDerived = luaClass;
        luaClass->prevSibling = 0;
        luaClass->base = base;
    }
}

/* Whether `tag` belongs to the class or a class derived from it; `distance` counts the
 * derivations down to the one it belongs to. */
int LuaClass_HasTag(LuaClass *luaClass, int tag, int *distance) {
    LuaClass *derived;

    if (tag == luaClass->instanceTag || tag == luaClass->referenceTag) {
        return 1;
    }
    *distance += 1;
    for (derived = luaClass->firstDerived; derived != 0; derived = derived->nextSibling) {
        if (LuaClass_HasTag(derived, tag, distance) != 0) {
            return 1;
        }
    }
    *distance -= 1;
    return 0;
}

/* The script function `getClassTags(class)`: the class table's tag, then the two instance tags. */
int LuaBinding_GetClassTags(lua_State *L) {
    LuaClass *luaClass;

    luaClass = (LuaClass *)lua_touserdata(L, 1);
    if (luaClass == 0) {
        LuaError("function getClassTags() requires class as argument");
        return 0;
    }
    lua_pushnumber(L, luaClass->classTag);
    lua_pushnumber(L, luaClass->instanceTag);
    lua_pushnumber(L, luaClass->referenceTag);
    return 3;
}
