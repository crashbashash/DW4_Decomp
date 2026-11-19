igMetaObject *g_igLuaGlue_metaObject;

igMetaObject *igLuaGlue_GetOrCreateMetaObject(void) {
    if (g_igLuaGlue_metaObject == 0) {
        g_igLuaGlue_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLuaGlue_metaObject;
}

igMetaObject *igLuaGlue_GetMetaObject(void)
{
    igMetaObject *meta = g_igLuaGlue_metaObject;
    if (!meta || isRegistered(meta) == false)
        igLuaGlue_EnsureRegistered();
    return g_igLuaGlue_metaObject;
}

int igLuaGlue_GetVTable(void) {
    igLuaGlue glue;

    return *(int *)((char *)&glue + g_objectSystem->vtableProbeOffset);
}

void igLuaGlue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLuaGlue_Register);
}

CallbackArray *igLuaGlue_Register(void) {
    LuaLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLuaGlue_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLuaGlue_GetMetaObject,
        "igLuaGlue",
        8, /* instance size */
        igLuaGlue_GetVTable,
        0, /* no reflected fields */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLuaGlue_GetMetaObject(void) {
    igLuaGlue_GetMetaObject();
}
