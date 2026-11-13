void LuaBinding_SetGlobalUserdata(lua_State *L, const char *name, void *object, int tag) {
    lua_getglobals(L);
    lua_pushstring(L, name);
    lua_pushusertag(L, object, tag);
    lua_rawset(L, -3);
    lua_settop(L, -2);
}

LuaStartupHook::LuaStartupHook(igLuaGlue::Class *(*create)(void), int phase) {
    this->phase = phase;
    this->create = create;
    next = g_luaStartupHooks;
    prev = 0;
    if (g_luaStartupHooks != 0) {
        g_luaStartupHooks->prev = this;
    }
    g_luaStartupHooks = this;
}

/* A type code of a binding table: kind in bits 0-4, indirection in 5-6, three flags in 7-9 and the
 * index of the class name in the rest. */
LuaType::LuaType(const char **names, unsigned int code) {
    *this = LuaType(code & 0x1f, (code >> 5) & 3, (code >> 7) & 7, names[(code >> 10) & 0x3fffff]);
}

void LuaType_UpdateAccepted(LuaType *type) {
    int accepts;

    accepts = type->byValue != 0;
    if (accepts != 0) {
        accepts = type->indirection > 0;
        if (accepts == 0) {
            accepts = type->kind != LUA_KIND_OBJECT;
        }
    }
    type->acceptsTable = accepts;
    accepts = type->indirection == 1;
    if (accepts != 0) {
        accepts = type->kind == LUA_KIND_OBJECT;
    }
    type->isObjectPointer = accepts;
    type->acceptedTypes = 0;
    if (type->indirection > 0) {
        if (type->kind == LUA_KIND_CHARS && type->indirection == 1) {
            type->acceptedTypes |= (1 << LUA_TNIL) | (1 << LUA_TSTRING);
        } else {
            type->acceptedTypes |= (1 << LUA_TUSERDATA) | (1 << LUA_TNIL);
        }
    } else if (type->kind == LUA_KIND_OBJECT) {
        type->acceptedTypes |= 1 << LUA_TUSERDATA;
    } else if (type->kind == LUA_KIND_ENUM) {
        type->acceptedTypes |= (1 << LUA_TNUMBER) | (1 << LUA_TSTRING);
    } else if (type->kind == LUA_KIND_STRING) {
        type->acceptedTypes |= (1 << LUA_TNIL) | (1 << LUA_TSTRING);
    } else if ((unsigned int)(type->kind - LUA_KIND_VOID) <= 1U || type->kind == LUA_KIND_NONE) {
        type->acceptedTypes = 0;
    } else {
        type->acceptedTypes |= 1 << LUA_TNUMBER;
    }
    if (type->byValue != 0) {
        type->acceptedTypes &= ~(1 << LUA_TNIL);
    }
    if (type->acceptsTable != 0 || type->isObjectPointer != 0) {
        type->acceptedTypes |= 1 << LUA_TTABLE;
    }
}

int LuaType_IsNumber(LuaType *type) {
    switch (type->kind) {
    case LUA_KIND_CHAR:
    case LUA_KIND_UCHAR:
    case LUA_KIND_SHORT:
    case LUA_KIND_USHORT:
    case LUA_KIND_INT:
    case LUA_KIND_UINT:
    case LUA_KIND_LONG:
    case LUA_KIND_ULONG:
    case LUA_KIND_BOOL:
    case LUA_KIND_FLOAT:
    case LUA_KIND_DOUBLE:
        return 1;
    default:
        return 0;
    }
}

/* Whether a userdata of `tag` can stand for `type`, and how many derivations away it is. */
int LuaType_MatchesUserdata(LuaType *type, int tag, LuaBoundObject *object, int *distance) {
    if (type->metaObject) {
        igMetaObject *meta;
        bool isObject = tag == g_luaObjectTag || g_luaObjectTags->indexOf(tag) >= 0;
        if (!isObject) {
            return 0;
        }
        *distance = 0;
        for (meta = object->getMeta(); meta; meta = (igMetaObject *)meta->_parent) {
            if (meta == type->metaObject) {
                return 1;
            }
            (*distance)++;
        }
        return 0;
    }
    if (type->luaClass) {
        *distance = 0;
        if (LuaClass_HasTag(type->luaClass, tag, distance)
            || (type->luaClass->alternate && LuaClass_HasTag(type->luaClass->alternate, tag, distance))) {
            return 1;
        }
        return 0;
    }
    return 1;
}

/* Pushes an object as userdata: tagged as a new instance, as a reference, or keeping the tag it
 * already has. A script's first reference to an Alchemy object adds one to its count. */
void LuaType_PushObject(LuaType *type, lua_State *L, LuaBoundObject *object, int mode) {
    igLuaGlue::Class *luaClass;

    if (object == 0) {
        lua_pushnil(L);
        return;
    }
    luaClass = type->luaClass;
    if (luaClass != 0) {
        if (type->metaObject != 0) {
            luaClass = LuaClass_FindForMeta(object->getMeta());
        }
        if (mode == LUA_PUSH_INSTANCE) {
            lua_pushusertag(L, object, luaClass->instanceTag);
        } else if (mode == LUA_PUSH_REFERENCE) {
            lua_pushusertag(L, object, luaClass->referenceTag);
        } else {
            lua_pushusertag(L, object, LUA_ANYTAG);
            if (lua_tag(L, -1) == 0) {
                lua_settag(L, luaClass->referenceTag);
            }
        }
    } else if (type->metaObject != 0) {
        lua_pushusertag(L, object, g_luaObjectTag);
    }
    if (type->metaObject != 0) {
        if (object->refBits.scriptHeld == 0) {
            object->refBits.scriptHeld = 1;
            object->_refCount = object->_refCount + 1;
        }
    }
}

void LuaType_PushString(LuaType *type, lua_State *L, const char *string) {
    if (string != 0) {
        lua_pushstring(L, string);
        return;
    }
    lua_pushnil(L);
}

void LuaType_PushPointer(LuaType *type, lua_State *L, int mode, LuaBoundObject *object) {
    if (type->indirection > 0 || type->kind == LUA_KIND_OBJECT) {
        LuaType_PushObject(type, L, object, mode);
        return;
    }
    LuaError("Unexpected return type");
}

/* How well the Lua value at `index` converts to `type`: 0 when it cannot. */
int LuaType_Accepts(LuaType *type, lua_State *L, int index, int *distance) {
    int luaType;
    int elementType;
    void *object;
    int tag;
    void *peer;

    *distance = 0;
    luaType = lua_type(L, index);
    if (!(type->acceptedTypes & (1 << luaType))) return 0;
    if (luaType == LUA_TTABLE) {
        if (LuaBinding_GetPeer(L, index) != 0) return type->isObjectPointer;
        if (type->acceptsTable != 0) {
            if (lua_getn(L, index) == 0) return 1;
            lua_rawgeti(L, index, 1);
            elementType = lua_type(L, -1);
            if (!(type->acceptedTypes & (1 << elementType))) {
                lua_settop(L, -2);
                return 0;
            }
            if (elementType == LUA_TUSERDATA) {
                tag = lua_tag(L, -1);
                object = lua_touserdata(L, -1);
                lua_settop(L, -2);
                return LuaType_MatchesUserdata(type, tag, (LuaBoundObject *)object, distance);
            }
            if (elementType == LUA_TTABLE) {
                peer = LuaBinding_GetPeer(L, -1);
                lua_settop(L, -2);
                return peer != 0;
            }
            lua_settop(L, -2);
            return 1;
        }
        return 0;
    } else if (luaType == LUA_TUSERDATA) {
        object = lua_touserdata(L, index);
        return LuaType_MatchesUserdata(type, lua_tag(L, index), (LuaBoundObject *)object, distance);
    } else {
        return 1;
    }
}

/* The type of a reflected field, from its meta-field class. A class whose name ends in
 * "MetaField" is a field of an embedded object of the class before the suffix. */
LuaType LuaType_FromMetaField(LuaMetaFieldView *field) {
    igMetaObject *meta = field->getMeta();
    LuaType result(LUA_KIND_NONE, 0, 0, 0);

    if (g_igCharMetaField_metaObject == meta) {
        result.kind = LUA_KIND_CHAR;
    } else if (g_igUnsignedCharMetaField_metaObject == meta) {
        result.kind = LUA_KIND_UCHAR;
    } else if (g_igIntMetaField_metaObject == meta) {
        result.kind = LUA_KIND_INT;
    } else if (g_igUnsignedIntMetaField_metaObject == meta) {
        result.kind = LUA_KIND_UINT;
    } else if (g_igShortMetaField_metaObject == meta) {
        result.kind = LUA_KIND_SHORT;
    } else if (g_igUnsignedShortMetaField_metaObject == meta) {
        result.kind = LUA_KIND_USHORT;
    } else if (g_igLongMetaField_metaObject == meta) {
        result.kind = LUA_KIND_LONG;
    } else if (g_igUnsignedLongMetaField_metaObject == meta) {
        result.kind = LUA_KIND_ULONG;
    } else if (g_igEnumMetaField_metaObject == meta) {
        result.kind = LUA_KIND_ENUM;
    } else if (g_igFloatMetaField_metaObject == meta) {
        result.kind = LUA_KIND_FLOAT;
    } else if (g_igDoubleMetaField_metaObject == meta) {
        result.kind = LUA_KIND_DOUBLE;
    } else if (g_igStringMetaField_metaObject == meta) {
        result.kind = LUA_KIND_STRING;
    } else if (g_igBoolMetaField_metaObject == meta) {
        result.kind = LUA_KIND_BOOL;
    } else if (g_igMemoryRefMetaField_metaObject == meta) {
        result = LuaType_FromMetaField((LuaMetaFieldView *)((igMemoryRefMetaField *)field)->_memType);
        result.indirection = 1;
        result.byValue = 0;
    } else if (g_igObjectRefMetaField_metaObject == meta) {
        result.kind = LUA_KIND_OBJECT;
        result.metaObject = (igMetaObject *)((igObjectRefMetaField *)field)->_metaObject;
        result.indirection = 1;
        if (result.metaObject != 0) {
            result.luaClass = LuaClass_FindByName((const char *)result.metaObject->_name);
        }
    } else {
        char *suffix = strstr((char *)meta->_name, "MetaField");
        if (suffix != 0) {
            *suffix = 0;
            result.kind = LUA_KIND_OBJECT;
            result.luaClass = LuaClass_FindByName((const char *)meta->_name);
            result.byValue = 1;
            *suffix = 'M';
        }
        if (result.luaClass == 0) {
            LuaError("Unsupported metafield type %s\n", meta->_name);
        }
    }
    LuaType_UpdateAccepted(&result);
    return result;
}

/* Stores a value back into slot 1 of the table at `table` (an argument passed in a table). */
void LuaValue_StoreInTable(LuaValue *value, lua_State *L, int table) {
    if (value->type.indirection > 0) {
        LuaType_PushObject(&value->type, L, (LuaBoundObject *)value->data.object, LUA_PUSH_KEEP_TAG);
    } else if (value->type.kind == LUA_KIND_ENUM) {
        lua_pushnumber(L, value->data.i);
    } else if (value->type.kind == LUA_KIND_STRING) {
        LuaType_PushString(&value->type, L, value->data.string);
    } else {
        switch (value->type.kind) {
        case LUA_KIND_CHAR:
            lua_pushnumber(L, value->data.c);
            break;
        case LUA_KIND_UCHAR:
            lua_pushnumber(L, value->data.uc);
            break;
        case LUA_KIND_SHORT:
            lua_pushnumber(L, value->data.s);
            break;
        case LUA_KIND_USHORT:
            lua_pushnumber(L, value->data.us);
            break;
        case LUA_KIND_INT:
            lua_pushnumber(L, value->data.i);
            break;
        case LUA_KIND_UINT:
            lua_pushnumber(L, value->data.ui);
            break;
        case LUA_KIND_LONG:
            lua_pushnumber(L, value->data.ll);
            break;
        case LUA_KIND_ULONG:
            lua_pushnumber(L, value->data.ull);
            break;
        case LUA_KIND_BOOL:
            lua_pushnumber(L, value->data.b);
            break;
        case LUA_KIND_FLOAT:
            lua_pushnumber(L, value->data.f);
            break;
        case LUA_KIND_DOUBLE:
            lua_pushnumber(L, value->data.d);
            break;
        }
    }
    lua_rawseti(L, table, 1);
}
