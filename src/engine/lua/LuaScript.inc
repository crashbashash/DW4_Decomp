int LuaBoolArray_Set(lua_State *L) {
    LuaClass *luaClass;
    bool *array;
    int index;

    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (lua_type(L, 2) != LUA_TNUMBER) {
        LuaError("%s: Non-number array access", luaClass->name);
        return 0;
    }
    array = (bool *)lua_touserdata(L, 1);
    index = (int)lua_tonumber(L, 2);
    if (lua_type(L, 3) != LUA_TNUMBER) {
        LuaError("Value to set must be number");
        return 0;
    }
    array[index] = lua_tonumber(L, 3) != 0;
    return 0;
}

/* Undoes LuaGlue_Initialize: empties the binding's tables, freeing what they own, and drops the
 * tag list and the pool. */
void LuaGlue_Shutdown(void) {
    LuaTagList *tags;
    igObject *pool;

    LuaConstantTable_Clear();
    LuaEnumTable_Clear();
    LuaPropertyTable_Clear();
    LuaFunctionTable_Clear();
    LuaClassTable_Clear();
    tags = g_luaObjectTags;
    tags->_refCount = tags->_refCount - 1;
    if ((tags->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(tags);
    }
    {
        LuaFieldWalker it;
        while (it.isValid()) {
            LuaFieldEntry *entry = it.get();
            it++;
            delete entry;
        }
    }
    pool = g_luaGluePool;
    if (pool != 0) {
        pool->_refCount = pool->_refCount - 1;
        if ((pool->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(pool);
        }
    }
}

LuaFieldWalker::~LuaFieldWalker() {
}

int LuaFieldWalker::isValid() {
    return node != 0;
}

LuaFieldEntry::~LuaFieldEntry() {
}

LuaFieldWalker &LuaFieldWalker::operator++(int) {
    node = (LuaFieldEntry *)node->link.next;
    if (node != 0) {
        /* the next entry of the same bucket */
    } else {
        while (node == 0 && bucket < g_luaFieldBucketCount) {
            node = (LuaFieldEntry *)g_luaFieldBuckets[bucket++];
        }
    }
    return *this;
}

LuaFieldEntry *LuaFieldWalker::get() {
    return node;
}

LuaFieldWalker::LuaFieldWalker() {
    node = 0;
    bucket = 0;
    while (node == 0 && bucket < g_luaFieldBucketCount && g_luaFieldBuckets != 0) {
        node = (LuaFieldEntry *)g_luaFieldBuckets[bucket++];
    }
}

/* The C++ object a script table stands for, in its `peer` field. */
void *LuaBinding_GetPeer(lua_State *L, int index) {
    void *peer;

    if (lua_type(L, index) != LUA_TTABLE) {
        return 0;
    }
    lua_pushstring(L, "peer");
    lua_rawget(L, index);
    peer = lua_touserdata(L, -1);
    lua_settop(L, -2);
    return peer;
}

/* The script function `new(table)`: follows the `base` fields to the class the table derives
 * from, runs its peer constructor (else its constructor) and links the new object's table to
 * the argument as its base. */
int LuaBinding_New(lua_State *L) {
    LuaClass *luaClass;
    char *peerName;
    lua_CFunction construct;

    if (LUA_TTABLE != lua_type(L, 1)) {
        LuaError("function new() requires base class table as argument!");
    }
    do {
        lua_pushstring(L, "base");
        lua_rawget(L, -2);
    } while (lua_type(L, -1) == LUA_TTABLE);
    luaClass = (LuaClass *)lua_touserdata(L, -1);
    if (0 == luaClass) {
        LuaError("new() requires that root table in table hierarchy have variable 'base = SomeC++Class'");
        return 0;
    }
    peerName = new char[strlen(luaClass->name) + 5];
    sprintf(peerName, "%sPeer", luaClass->name);
    lua_getglobals(L);
    lua_pushstring(L, peerName);
    lua_rawget(L, -2);
    construct = lua_tocfunction(L, -1);
    delete[] peerName;
    if (construct == 0) {
        lua_settop(L, -2);
        lua_pushstring(L, luaClass->name);
        lua_rawget(L, -2);
        construct = lua_tocfunction(L, -1);
        if (!construct) {
            LuaError("new() Cannot find peer constructor %s()", luaClass->name);
            return 0;
        }
    }
    construct(L);
    lua_pushstring(L, "base");
    lua_pushvalue(L, 1);
    lua_rawset(L, -3);
    return 1;
}

/* The script function `cast(className, object)`: the object as userdata of the named class, when
 * that class derives from the object's. Both tests compare the same way round. */
int LuaBinding_Cast(lua_State *L) {
    const char *className;
    LuaClass *from;
    LuaClass *to;
    void *object;
    bool derived;
    LuaClass *c;

    if (lua_type(L, 1) != LUA_TSTRING) {
        LuaError("function cast() requires classname as first arg");
    }
    if (lua_type(L, 2) != LUA_TUSERDATA) {
        LuaError("function cast() requires userdata object as second arg");
    }
    className = lua_tostring(L, 1);
    from = LuaClass_FindByTag(lua_tag(L, 2));
    if (from == 0) {
        return 0;
    }
    to = LuaClass_FindByName(className);
    if (to == 0) {
        return 0;
    }
    object = lua_touserdata(L, 2);
    derived = false;
    for (c = to; c != 0; c = c->base) {
        if (c == from) {
            derived = true;
        }
    }
    if (!derived) {
        for (c = to; c != 0; c = c->base) {
            if (c == from) {
                derived = true;
            }
        }
    }
    if (!derived) {
        return 0;
    }
    lua_pushusertag(L, object, from->instanceTag != 0 ? to->instanceTag : to->referenceTag);
    return 1;
}
