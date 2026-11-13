/* An ig*Array class: a Lua class of its own vtable, no meta-object and no peer constructor. */
struct LuaArrayClass : LuaClass {
    LuaArrayClass(const char *name, const void *vtable, lua_CFunction gc, lua_CFunction get,
                  lua_CFunction set, lua_CFunction construct)
        : LuaClass(name, 0, gc, 0, get, set, construct) {
        this->vtable = vtable;
    }
};

/* Builds the array classes, creates every class a start-up hook registers (phase 0 first),
 * lets each bind its functions and constants, then links the overloads. */
void LuaGlue_Initialize(void) {
    LuaStartupHook *hook;

    if (g_luaGluePool == 0) {
        g_luaGluePool = Memory_GetCurrentContextAlias()->getPool(16);
        g_luaGluePool->_refCount = g_luaGluePool->_refCount + 1;
        g_luaArrayClasses[LUA_KIND_CHAR] = new (g_luaGluePool) LuaArrayClass(
            "igCharArray", g_LuaCharArrayClass_vtable,
            LuaCharArray_Delete, LuaCharArray_Get, LuaCharArray_Set, LuaCharArray_New);
        g_luaArrayClasses[LUA_KIND_UCHAR] = new (g_luaGluePool) LuaArrayClass(
            "igUnsignedCharArray", g_LuaUnsignedCharArrayClass_vtable,
            LuaUnsignedCharArray_Delete, LuaUnsignedCharArray_Get, LuaUnsignedCharArray_Set, LuaUnsignedCharArray_New);
        g_luaArrayClasses[LUA_KIND_SHORT] = new (g_luaGluePool) LuaArrayClass(
            "igShortArray", g_LuaShortArrayClass_vtable,
            LuaShortArray_Delete, LuaShortArray_Get, LuaShortArray_Set, LuaShortArray_New);
        g_luaArrayClasses[LUA_KIND_USHORT] = new (g_luaGluePool) LuaArrayClass(
            "igUnsignedShortArray", g_LuaUnsignedShortArrayClass_vtable,
            LuaUnsignedShortArray_Delete, LuaUnsignedShortArray_Get, LuaUnsignedShortArray_Set,
            LuaUnsignedShortArray_New);
        g_luaArrayClasses[LUA_KIND_INT] = new (g_luaGluePool) LuaArrayClass(
            "igIntArray", g_LuaIntArrayClass_vtable,
            LuaIntArray_Delete, LuaIntArray_Get, LuaIntArray_Set, LuaIntArray_New);
        g_luaArrayClasses[LUA_KIND_UINT] = new (g_luaGluePool) LuaArrayClass(
            "igUnsignedIntArray", g_LuaUnsignedIntArrayClass_vtable,
            LuaUnsignedIntArray_Delete, LuaUnsignedIntArray_Get, LuaUnsignedIntArray_Set, LuaUnsignedIntArray_New);
        g_luaArrayClasses[LUA_KIND_LONG] = new (g_luaGluePool) LuaArrayClass(
            "igLongArray", g_LuaLongArrayClass_vtable,
            LuaLongArray_Delete, LuaLongArray_Get, LuaLongArray_Set, LuaLongArray_New);
        g_luaArrayClasses[LUA_KIND_ULONG] = new (g_luaGluePool) LuaArrayClass(
            "igUnsignedLongArray", g_LuaUnsignedLongArrayClass_vtable,
            LuaUnsignedLongArray_Delete, LuaUnsignedLongArray_Get, LuaUnsignedLongArray_Set,
            LuaUnsignedLongArray_New);
        g_luaArrayClasses[LUA_KIND_BOOL] = new (g_luaGluePool) LuaArrayClass(
            "igBoolArray", g_LuaBoolArrayClass_vtable,
            LuaBoolArray_Delete, LuaBoolArray_Get, LuaBoolArray_Set, LuaBoolArray_New);
        g_luaArrayClasses[LUA_KIND_FLOAT] = new (g_luaGluePool) LuaArrayClass(
            "igFloatArray", g_LuaFloatArrayClass_vtable,
            LuaFloatArray_Delete, LuaFloatArray_Get, LuaFloatArray_Set, LuaFloatArray_New);
        g_luaArrayClasses[LUA_KIND_DOUBLE] = new (g_luaGluePool) LuaArrayClass(
            "igDoubleArray", g_LuaDoubleArrayClass_vtable,
            LuaDoubleArray_Delete, LuaDoubleArray_Get, LuaDoubleArray_Set, LuaDoubleArray_New);
        g_luaArrayClasses[LUA_KIND_ENUM] = g_luaArrayClasses[LUA_KIND_INT];
        if (g_luaObjectTags == 0) {
            g_luaObjectTags = igIntList_Create(g_luaGluePool);
        }
        for (hook = g_luaStartupHooks; hook != 0; hook = hook->next) {
            if (hook->phase == 0) hook->luaClass = hook->create();
        }
        for (hook = g_luaStartupHooks; hook != 0; hook = hook->next) {
            if (hook->phase == 1) hook->luaClass = hook->create();
        }
        for (hook = g_luaStartupHooks; hook != 0; hook = hook->next) {
            hook->luaClass->registerFunctions();
            hook->luaClass->registerConstants();
        }
        g_luaStartupHooks = 0;
        LuaFunctionTable_LinkOverloads();
    }
}

/* LuaClass's own two virtual functions: a class with nothing more to bind. */
void LuaClass_RegisterConstants(LuaClass *luaClass) {
}

void LuaClass_RegisterFunctions(LuaClass *luaClass) {
}
