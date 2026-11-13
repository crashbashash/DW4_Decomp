/* The field of `meta` named `name`, from the binding's table of the fields it exposes. */
static inline igMetaField *LuaFieldTable_Find(igMetaObject *meta, const char *name) {
    LuaFieldIterator it(LuaFieldTable_Key(meta, name));

    while (it.isValid()) {
        LuaFieldEntry *entry = it.get();
        if (entry->meta == meta && strcmp(LuaMetaField_GetName(entry->field), name) == 0) {
            return entry->field;
        }
        it++;
    }
    return 0;
}

/* The `function` tag method of a bound meta-object: creates an instance and sets the fields a
 * table argument names. */
int LuaObject_New(lua_State *L) {
    igMetaObject *meta;
    igLuaGlue::Class *luaClass;
    int tag;
    LuaBoundObject *object;
    const char *key;
    igMetaField *field;

    if (g_luaMetaObjectTag == lua_tag(L, 1)) {
        meta = (igMetaObject *)lua_touserdata(L, 1);
        tag = g_luaObjectTag;
        luaClass = 0;
    } else {
        luaClass = (igLuaGlue::Class *)lua_touserdata(L, -1);
        meta = luaClass->metaObject;
        tag = luaClass->instanceTag;
    }
    object = (LuaBoundObject *)igMetaObject_CreateInstanceDefault(meta);
    if (lua_type(L, 2) == LUA_TTABLE) {
        lua_pushnil(L);
        while (lua_next(L, 2)) {
            key = lua_tostring(L, -2);
            if (luaClass) {
                field = LuaFieldTable_Find(meta, key);
            } else {
                field = igMetaObject_FindFieldByName(meta, key);
            }
            LuaObject_SetField(L, field, object, key, -1);
            lua_settop(L, -2);
        }
    }
    object->refBits.scriptHeld = 1;
    lua_pushusertag(L, object, tag);
    return 1;
}

int LuaFieldIterator::isValid() {
    return node != 0;
}

LuaFieldIterator &LuaFieldIterator::operator++(int) {
    node = (LuaFieldEntry *)node->link.next;
    return *this;
}

LuaFieldIterator::~LuaFieldIterator() {
}

const char *LuaMetaField_GetName(igMetaField *field) {
    return (const char *)field->_fieldName;
}

LuaFieldEntry *LuaFieldIterator::get() {
    return node;
}

LuaFieldIterator::LuaFieldIterator(unsigned int key)
    : node(g_luaFieldBuckets != 0
               ? (LuaFieldEntry *)g_luaFieldBuckets[(g_luaFieldBucketCount - 1) & (key ^ (key >> g_luaFieldBucketShift))]
               : 0) {
}

unsigned int LuaFieldTable_Key(igMetaObject *meta, const char *name) {
    return (unsigned int)meta ^ LuaBinding_HashName(name);
}

/* The `gc` tag method of bound objects: drops the script's reference, through the peer of a
 * table that stands for one. */
int LuaObject_Collect(lua_State *L) {
    LuaBoundObject *object;

    if (lua_type(L, 1) == LUA_TTABLE) {
        lua_pushstring(L, "peer");
        lua_rawget(L, 1);
        object = (LuaBoundObject *)lua_touserdata(L, -1);
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
        return 0;
    } else {
        object = (LuaBoundObject *)lua_touserdata(L, 1);
        object->refBits.scriptHeld = 0;
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
    return 0;
}

/* Calls a function stored in a class table, the class userdata the first argument. */
int LuaFunction_CallMember(lua_State *L) {
    LuaFunction *function;

    function = (LuaFunction *)lua_touserdata(L, -1);
    lua_remove(L, 1);
    if (function->isUnique == 0) {
        return LuaFunction_CallOverload(L);
    }
    if (function->argCount) {
        return LuaFunction_Call(function, L);
    }
    return function->function(L);
}

int LuaFunction_CallUpvalue(lua_State *L) {
    return LuaFunction_Call((LuaFunction *)lua_touserdata(L, -1), L);
}

/* Calls the overload whose argument types fit the call best. */
int LuaFunction_CallOverload(lua_State *L) {
    LuaFunction *function;
    const char *name;
    igLuaGlue::Class *owner;
    LuaFunction *chosen;

    function = (LuaFunction *)lua_touserdata(L, -1);
    name = function->name;
    owner = function->owner;
    chosen = LuaFunction_Resolve(function, L, function->hasSelf ? 2 : 1, -2);
    if (chosen != 0) {
        if (function != chosen) {
            lua_settop(L, -2);
            lua_pushusertag(L, chosen, 0);
        }
        return LuaFunction_Call(chosen, L);
    }
    LuaError("Cannot find enum or function %s::%s with appropriate arguments.\n"
             "Make sure you use the obj:foo() syntax for member functions!!!", owner->name, name);
    return 0;
}

/* Reads a member of a class: a value of its class table, a property, or an enum constant. */
int LuaClass_GetMember(lua_State *L, igLuaGlue::Class *luaClass, const char *name) {
    igLuaGlue::Class *c;
    LuaProperty *property;
    LuaConstant *constant;

    for (c = luaClass; c != 0; c = c->base) {
        lua_getref(L, c->classTableRef);
        lua_pushvalue(L, 2);
        lua_rawget(L, -2);
        if (lua_type(L, -1) != LUA_TNIL) {
            return 1;
        }
        lua_settop(L, -3);
        property = LuaPropertyTable_Find(c, name);
        if (property != 0) {
            lua_settop(L, -2);
            lua_pushusertag(L, property, 0);
            return property->owner->getHandler(L);
        }
    }
    constant = LuaConstantTable_Find(name, luaClass);
    if (constant != 0) {
        lua_pushnumber(L, constant->value);
        return 1;
    }
    LuaError("Cannot find field \"%s\" on class \"%s\"", name, luaClass->name);
    return 0;
}

int LuaClass_GetIndexed(lua_State *L, igLuaGlue::Class *luaClass) {
    igLuaGlue::Class *c;

    for (c = luaClass; c != 0; c = c->base) {
        if (c->indexGetter != 0) {
            lua_settop(L, -2);
            lua_pushusertag(L, c->indexGetter, 0);
            return c->indexGetter->function(L);
        }
    }
    LuaError("Class \"%s\" does not have operator[] - cannot index this object", luaClass->name);
    return 0;
}

/* The `gettable` tag method of class tables and of objects without a meta-object. */
int LuaClass_GetTable(lua_State *L) {
    igLuaGlue::Class *luaClass;

    if (LuaBinding_GetPeer(L, 1) != 0) {
        return LuaPeer_GetTable(L);
    }
    if (lua_type(L, 2) == LUA_TSTRING) {
        luaClass = (igLuaGlue::Class *)lua_touserdata(L, -1);
        return LuaClass_GetMember(L, luaClass, lua_tostring(L, 2));
    }
    return LuaClass_GetIndexed(L, (igLuaGlue::Class *)lua_touserdata(L, -1));
}

/* The `settable` tag method of class tables and of objects without a meta-object. */
int LuaClass_SetTable(lua_State *L) {
    int keyType;
    igLuaGlue::Class *c;
    LuaProperty *property;
    const char *name;
    igLuaGlue::Class *luaClass;

    if (LuaBinding_GetPeer(L, 1) != 0) {
        return LuaPeer_SetTable(L);
    }
    keyType = lua_type(L, 2);
    if (keyType == LUA_TSTRING) {
        name = lua_tostring(L, 2);
    } else {
        name = 0;
    }
    c = (igLuaGlue::Class *)lua_touserdata(L, -1);
    for (; c != 0; c = c->base) {
        if (name != 0) {
            property = LuaPropertyTable_Find(c, name);
            if (property != 0) {
                lua_settop(L, -2);
                lua_pushusertag(L, property, 0);
                return property->owner->setHandler(L);
            }
        } else if (c->indexSetter != 0) {
            lua_settop(L, -2);
            lua_pushusertag(L, c->indexSetter, 0);
            return c->indexSetter->function(L);
        }
    }
    luaClass = (igLuaGlue::Class *)lua_touserdata(L, -1);
    if (keyType == LUA_TSTRING) {
        LuaError("Cannot find field \"%s\" on class \"%s\"", name, luaClass->name);
    } else {
        LuaError("Class \"%s\" does not have operator[] - cannot index this object", luaClass->name);
    }
    return 0;
}

/* The `gettable` tag method of objects with a meta-object: a reflected field, else a member of
 * the class. */
int LuaObject_GetTable(lua_State *L) {
    int tag;
    int keyType;
    LuaBoundObject *object;
    igMetaObject *meta;
    igLuaGlue::Class *luaClass;
    igMetaField *field;
    const char *key;

    if (LuaBinding_GetPeer(L, 1) != 0) {
        return LuaPeer_GetTable(L);
    }
    tag = lua_tag(L, 1);
    keyType = lua_type(L, 2);
    object = (LuaBoundObject *)lua_touserdata(L, 1);
    meta = object->getMeta();
    if (tag != g_luaObjectTag) {
        luaClass = (igLuaGlue::Class *)lua_touserdata(L, -1);
        if (keyType == LUA_TSTRING) {
            key = lua_tostring(L, 2);
            field = LuaFieldTable_Find(meta, key);
            return field ? LuaObject_PushField(L, field, object) : LuaClass_GetMember(L, luaClass, key);
        } else {
            return LuaClass_GetIndexed(L, luaClass);
        }
    } else if (keyType == LUA_TSTRING) {
        field = igMetaObject_FindFieldByName(meta, lua_tostring(L, 2));
        if (field) {
            return LuaObject_PushField(L, field, object);
        }
        return 0;
    }
    LuaError("Class \"%s\" does not have operator[] - cannot index this object", meta->_name);
    return 0;
}

/* The `settable` tag method of objects with a meta-object. */
int LuaObject_SetTable(lua_State *L) {
    LuaBoundObject *object;
    igMetaObject *meta;
    int keyType;
    int tag;
    const char *key;

    if (LuaBinding_GetPeer(L, 1) != 0) {
        return LuaPeer_SetTable(L);
    }
    tag = lua_tag(L, 1);
    keyType = lua_type(L, 2);
    object = (LuaBoundObject *)lua_touserdata(L, 1);
    meta = object->getMeta();
    if (tag != g_luaObjectTag) {
        if (keyType == LUA_TSTRING) {
            key = lua_tostring(L, 2);
            LuaObject_SetField(L, LuaFieldTable_Find(meta, key), object, key, 3);
            return 0;
        }
        return LuaClass_SetTable(L);
    }
    if (keyType == LUA_TSTRING) {
        key = lua_tostring(L, 2);
        LuaObject_SetField(L, igMetaObject_FindFieldByName(meta, key), object, key, 3);
    } else {
        LuaError("Class \"%s\" does not have operator[] - cannot index this object", meta->_name);
    }
    return 0;
}

/* Reads a key of a script table that extends a C++ object: the table itself, the tables its
 * `base` fields chain to, then the object in its `peer` field. */
int LuaPeer_GetTable(lua_State *L) {
    lua_pushvalue(L, 2);
    lua_rawget(L, 1);
    if (lua_type(L, -1) != LUA_TNIL) {
        return 1;
    }
    lua_settop(L, -2);
    lua_pushvalue(L, 1);
    for (;;) {
        lua_pushstring(L, "base");
        lua_rawget(L, -2);
        if (lua_type(L, -1) != LUA_TTABLE) {
            break;
        }
        lua_pushvalue(L, 2);
        lua_rawget(L, -2);
        if (lua_type(L, -1) != LUA_TNIL) {
            return 1;
        }
        lua_settop(L, -2);
    }
    lua_pushstring(L, "peer");
    lua_rawget(L, 1);
    lua_pushvalue(L, 2);
    lua_gettable(L, -2);
    return 1;
}

static bool s_peerSetFailed;

void LuaPeer_NoteSetError(const char *message, void *data) {
    s_peerSetFailed = 1;
}

/* Writes a key of such a table: to the object when it has the field, else to the table. */
int LuaPeer_SetTable(lua_State *L) {
    void *data;
    LuaErrorHandler handler;

    lua_pushvalue(L, 2);
    lua_rawget(L, 1);
    if (lua_type(L, -1) == LUA_TNIL) {
        lua_settop(L, -2);
        lua_pushstring(L, "peer");
        lua_rawget(L, 1);
        handler = LuaBinding_GetErrorHandler(&data);
        LuaBinding_SetErrorHandler(LuaPeer_NoteSetError, L);
        s_peerSetFailed = 0;
        lua_pushvalue(L, 2);
        lua_pushvalue(L, 3);
        lua_settable(L, -3);
        LuaBinding_SetErrorHandler(handler, data);
        if (s_peerSetFailed == 0) {
            return 0;
        }
    }
    lua_pushvalue(L, 2);
    lua_pushvalue(L, 3);
    lua_rawset(L, 1);
    return 0;
}

void LuaObject_SetField(lua_State *L, igMetaField *field, LuaBoundObject *object, const char *key, int index) {
    if (field == 0) {
        LuaError("Cannot find field \"%s\" on class \"%s\"", key, object->getMeta()->_name);
        return;
    }
    if (LuaObject_StoreField(L, field, object, index) == 0) {
        LuaError("Unsupported field \"%s\" on class \"%s\"", key, object->getMeta()->_name);
    }
}

/* The tag method an operator binds: the operands first, the function as the upvalue. */
int LuaFunction_CallOperator(lua_State *L) {
    LuaFunction *function;
    int tag;
    igLuaGlue::Class *owner;

    function = (LuaFunction *)lua_touserdata(L, -1);
    tag = lua_tag(L, 1);
    owner = function->owner;
    if (tag == owner->instanceTag || tag == owner->referenceTag) {
        lua_remove(L, 3);
    } else {
        lua_settop(L, -3);
        lua_insert(L, 1);
        lua_pushusertag(L, function, 0);
    }
    if (function->isUnique == 0) {
        return LuaFunction_CallOverload(L);
    }
    if (function->argCount != 0) {
        return LuaFunction_Call(function, L);
    }
    return function->function(L);
}

int LuaFunction_CallUnaryOperator(lua_State *L) {
    LuaFunction *function;

    function = (LuaFunction *)lua_touserdata(L, -1);
    lua_remove(L, 2);
    lua_remove(L, 2);
    return function->function(L);
}
