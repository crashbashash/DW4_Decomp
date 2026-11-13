LuaFunction::LuaFunction(lua_CFunction function, int id, const char *name, const LuaType &result,
                         igLuaGlue::Class *owner, int isMethod, int argCount)
    : Hashed<LuaFunction, 8>((unsigned int)owner ^ LuaBinding_HashName(name)) {
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

/* The function `name` of `owner` or of its nearest base class that has one: a callback (a
 * function with a negative id) or not, as `callback` asks. */
LuaFunction *LuaFunctionTable_Find(igLuaGlue::Class *owner, const char *name, bool callback) {
    igLuaGlue::Class *luaClass;

    for (luaClass = owner; luaClass != 0; luaClass = luaClass->base) {
        LuaTableIterator<LuaFunction> it((unsigned int)luaClass ^ LuaBinding_HashName(name));

        while (it.isValid()) {
            LuaFunction *function = it.get();
            if (callback == (function->id < 0) && strcmp(function->name, name) == 0
                && function->owner == luaClass) {
                return function;
            }
            it++;
        }
    }
    return 0;
}

/* The overload of `function` that best takes the arguments from `first` to `last`: the one whose
 * conversions go through the fewest derivations, searched in the owner and then in each base
 * class that has a function of the name. */
LuaFunction *LuaFunction_Resolve(LuaFunction *function, lua_State *L, int first, int last) {
    int top;
    igLuaGlue::Class *owner;
    int argCount;
    LuaFunction *best;
    LuaFunction *overload;
    int bestScore;
    int score;
    LuaType *argTypes;
    int i;
    int distance;

    top = lua_gettop(L);
    if (first < 0) {
        first += top;
    }
    if (last < 0) {
        last += top + 1;
    }
    owner = function->owner;
    argCount = last - first + 1;
    do {
        best = 0;
        overload = function;
        bestScore = 999999;
        do {
            if (overload->argCount == argCount) {
                argTypes = (LuaType *)(overload + 1);
                score = 0;
                for (i = 0; i < argCount; i++) {
                    if (!LuaType_Accepts(&argTypes[i], L, first + i, &distance)) goto next;
                    score += distance;
                }
                if (score == 0) {
                    return overload;
                }
                if (score == bestScore) {
                    LuaError("%s::%s - Overloads have similar conversions", owner->name, function->name);
                }
                if (score < bestScore) {
                    bestScore = score;
                    best = overload;
                }
            }
        next:
            overload = overload->nextOverload;
        } while (overload != 0 && overload != function);
        if (best != 0) {
            return best;
        }
        if (function->result.kind == LUA_KIND_STATIC) {
            return 0;
        }
        owner = owner->base;
        if (owner == 0) {
            return 0;
        }
        {
            LuaTableIterator<LuaFunction> it((unsigned int)owner ^ LuaBinding_HashName(function->name));

            while (true) {
                function = it.get();
                if (function == 0) {
                    return 0;
                }
                if (function->owner == owner && strcmp(function->name, overload->name) == 0) {
                    break;
                }
                it++;
            }
        }
    } while (owner != 0);
    return 0;
}

/* Chains the functions of one name and owner into a ring of overloads, and marks a function
 * that shares its name with one of a base class as not unique either. */
void LuaFunctionTable_LinkOverloads(void) {
    LuaTableWalker<LuaFunction> walker;

    while (walker.isValid()) {
        LuaFunction *function = walker.get();
        igLuaGlue::Class *base;
        LuaFunction *last = 0;

        if (function->nextOverload == 0) {
            igLuaGlue::Class *owner = function->owner;

            for (LuaTableIterator<LuaFunction> it((unsigned int)owner ^ LuaBinding_HashName(function->name));
                 it.isValid(); it++) {
                LuaFunction *other = it.get();
                if (function != other && other->owner == function->owner
                    && strcmp(function->name, other->name) == 0) {
                    function->isUnique = other->isUnique = 0;
                    other->nextOverload = function->nextOverload;
                    function->nextOverload = other;
                    if (last == 0) {
                        last = other;
                    }
                }
            }
        }
        if (last != 0) {
            last->nextOverload = function;
        }
        for (base = function->owner->base; base != 0; base = base->base) {
            for (LuaTableIterator<LuaFunction> it((unsigned int)base ^ LuaBinding_HashName(function->name));
                 it.isValid(); it++) {
                LuaFunction *other = it.get();
                if (other->owner == base && strcmp(function->name, other->name) == 0) {
                    function->isUnique = other->isUnique = 0;
                }
            }
        }
        walker++;
    }
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

/* Binds every function of the function table to its class: a function named as its class is the
 * class's constructor, the arithmetic and comparison operators become tag methods, `operator[]`
 * the index handlers, and any other function, with `==`, `!=` and `=` under the names `equals`,
 * `notequals` and `copy` unless the class binds those itself, a field of the class table. */
void LuaFunctionTable_BindAll(lua_State *L) {
    LuaTableWalker<LuaFunction> it;
    while (it.isValid()) {
        LuaFunction *function = it.get();
        int i;
        LuaType *argTypes = (LuaType *)(function + 1);

        for (i = 0; i < function->argCount; i++) {
            if (argTypes[i].acceptsTable) {
                function->hasOutArgs = 1;
                break;
            }
        }
        if (function->id >= 0) {
            if (strcmp(function->owner->name, function->name) == 0) {
                lua_pushusertag(L, function, 0);
                lua_pushcclosure(L, LuaFunction_CallMember, 1);
                lua_settagmethod(L, function->owner->classTag, "function");
            } else if (strcmp("operator+", function->name) == 0) {
                LuaClass_SetOperator(L, function->owner, function, 0);
            } else if (strcmp("operator-", function->name) == 0) {
                if (!function->argCount) {
                    lua_pushusertag(L, function, 0);
                    lua_pushcclosure(L, LuaFunction_CallUnaryOperator, 1);
                    lua_pushvalue(L, -1);
                    lua_settagmethod(L, function->owner->instanceTag, "unm");
                    lua_settagmethod(L, function->owner->referenceTag, "unm");
                } else {
                    LuaClass_SetOperator(L, function->owner, function, 1);
                }
            } else if (strcmp("operator*", function->name) == 0) {
                LuaClass_SetOperator(L, function->owner, function, 2);
            } else if (strcmp("operator/", function->name) == 0) {
                LuaClass_SetOperator(L, function->owner, function, 3);
            } else if (strcmp("operator^", function->name) == 0) {
                LuaClass_SetOperator(L, function->owner, function, 4);
            } else if (strcmp("operator<", function->name) == 0) {
                LuaClass_SetOperator(L, function->owner, function, 6);
            } else if (strcmp("operator[]", function->name) == 0) {
                if (function->result.byValue) {
                    function->owner->indexSetter = function;
                    if (function->owner->indexGetter == 0) {
                        function->owner->indexGetter = function;
                    }
                } else {
                    function->owner->indexGetter = function;
                }
            } else {
                lua_getref(L, function->owner->classTableRef);
                if (strcmp("operator==", function->name) == 0 && LuaFunctionTable_Find(function->owner, "equals", 0) == 0) {
                    lua_pushstring(L, "equals");
                } else if (strcmp("operator!=", function->name) == 0 &&
                           LuaFunctionTable_Find(function->owner, "notequals", 0) == 0) {
                    lua_pushstring(L, "notequals");
                } else if (strcmp("operator=", function->name) == 0 && LuaFunctionTable_Find(function->owner, "copy", 0) == 0) {
                    lua_pushstring(L, "copy");
                } else {
                    lua_pushstring(L, function->name);
                }
                LuaFunction_SetField(L, function);
                lua_settop(L, -2);
            }
        }
        it++;
    }
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

/* Empties the function table, freeing every function. */
void LuaFunctionTable_Clear(void) {
    LuaTableWalker<LuaFunction> it;
    while (it.isValid()) {
        LuaFunction *function = it.get();
        it++;
        delete function;
    }
}

/* The property of a name that a class itself binds, 0 when it has none. */
LuaProperty *LuaPropertyTable_Find(igLuaGlue::Class *owner, const char *name) {
    LuaTableIterator<LuaProperty> it((unsigned int)owner ^ LuaBinding_HashName(name));
    while (it.isValid()) {
        LuaProperty *property = it.get();
        if (property->owner == owner && strcmp(property->name, name) == 0) {
            return property;
        }
        it++;
    }
    return 0;
}

/* Empties the property table. */
void LuaPropertyTable_Clear(void) {
    LuaTableWalker<LuaProperty> it;
    while (it.isValid()) {
        LuaProperty *property = it.get();
        it++;
        property->~LuaProperty();
    }
}

/* The constant of a name in an enum of a class or of one of its bases, 0 when there is none. */
LuaConstant *LuaConstantTable_Find(const char *name, igLuaGlue::Class *owner) {
    LuaTableIterator<LuaConstant> it(LuaBinding_HashName(name));
    while (it.isValid()) {
        LuaConstant *constant = it.get();
        if (strcmp(constant->name, name) == 0 && LuaClass_DistanceToBase(constant->enumeration->owner, owner) >= 0) {
            return constant;
        }
        it++;
    }
    return 0;
}

/* Empties the enum table, freeing every enum. */
void LuaEnumTable_Clear(void) {
    LuaTableWalker<LuaEnum> it;
    while (it.isValid()) {
        LuaEnum *enumeration = it.get();
        it++;
        delete enumeration;
    }
}

/* Empties the constant table. */
void LuaConstantTable_Clear(void) {
    LuaTableWalker<LuaConstant> it;
    while (it.isValid()) {
        LuaConstant *constant = it.get();
        it++;
        constant->~LuaConstant();
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
