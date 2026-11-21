igMetaObject *g_igLuaState_metaObject;
igMetaField *g_igLuaState_luaStateMetaField;
igMetaField *g_igLuaState_memPoolMetaField;

igMetaObject *igLuaState_GetMetaObject(void)
{
    igMetaObject *meta = g_igLuaState_metaObject;
    if (!meta || isRegistered(meta) == false)
        igLuaState_EnsureRegistered();
    return g_igLuaState_metaObject;
}

int igLuaState_GetVTable(void) {
    LuaStateImage state;
    int vtable;
    char **name;
    igObject **memPool;

    igObject_InitHeader((igObject *)&state);
    name = &state._name;
    *name = 0;
    state.vtable = g_igLuaState_vtable;
    memPool = &state._memPool;
    *memPool = 0;
    vtable = *(int *)((char *)&state + g_objectSystem->vtableProbeOffset);
    /* The destructors, each testing its member's address as a member destructor does. */
    state.vtable = g_igLuaState_vtable;
    if (memPool != 0) {
        igObject::release(*memPool);
    }
    state.vtable = g_igNamedObject_vtable;
    if (name != 0) {
        releaseString(*name);
    }
    return vtable;
}

void igLuaState_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLuaState_Register);
}

static igMetaObjectCallback g_igLuaState_callbackList[] = {igMemoryPool_EnsureRegistered, 0};

CallbackArray *igLuaState_Register(void) {
    LuaLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLuaState_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igLuaState_GetMetaObject,
        "igLuaState",
        0x14, /* instance size */
        igLuaState_GetVTable,
        igLuaState_InitFields,
        0, /* extra callback item */
        g_igLuaState_callbackList /* callback list */
    );
}

void thunk_igLuaState_GetMetaObject(void) {
    igLuaState_GetMetaObject();
}

static FieldFactory g_igLuaState_fieldConstructors[] = {
    igRawRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igLuaState_fieldNames[] = {
    "_luaState",
    "_memPool",
};
static igMetaField **g_igLuaState_fieldDescriptors[] = {
    &g_igLuaState_luaStateMetaField,
    &g_igLuaState_memPoolMetaField,
};
static int g_igLuaState_fieldOffsets[] = {
    12,
    16,
};

void igLuaState_InitFields(void) {
    igMetaObject *meta = g_igLuaState_metaObject;
    int first = igMetaObject_GetFieldCount(meta);
    igObjectRefMetaField *memPool;

    igMetaObject_CreateFields(meta, g_igLuaState_fieldConstructors, 2);
    memPool = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, first + 1);
    memPool->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igLuaState_fieldNames, g_igLuaState_fieldDescriptors, g_igLuaState_fieldOffsets, first);
}
