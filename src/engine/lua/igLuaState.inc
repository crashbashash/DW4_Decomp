igMetaObject *igLuaState_GetMetaObject(void)
{
    igMetaObject *meta = g_igLuaState_metaObject[0];
    if (!meta || isRegistered(meta) == false)
        igLuaState_EnsureRegistered();
    return g_igLuaState_metaObject[0];
}

int igLuaState_GetVTable(void) {
    LuaStateImage state;
    int vtable;
    char **name;
    igObject **memPool;

    igObject_InitHeader(&state);
    name = &state._name;
    *name = 0;
    state.vtable = g_igLuaState_vtable;
    memPool = &state._memPool;
    *memPool = 0;
    vtable = *(int *)((char *)&state + g_objectSystem[0]->vtableOffset);
    /* The destructors, each testing its member's address as a member destructor does. */
    state.vtable = g_igLuaState_vtable;
    if (memPool != 0) {
        igRelease(*memPool);
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

void *igLuaState_Register(void) {
    LuaLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLuaState_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igLuaState_GetMetaObject,
        igLuaState_className,
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

void igLuaState_InitFields(void) {
    igMetaObject *meta = g_igLuaState_metaObject[0];
    int first = igMetaObject_GetFieldCount(meta);
    igObjectRefMetaField *memPool;

    igMetaObject_CreateFields(meta, g_igLuaState_fieldConstructors, 2);
    memPool = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, first + 1);
    memPool->_metaObject = igMemoryPool_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igLuaState_fieldNames, g_igLuaState_fieldDescriptors, g_igLuaState_fieldOffsets, first);
}
