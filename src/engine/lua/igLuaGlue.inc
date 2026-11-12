igMetaObject *igLuaGlue_GetOrCreateMetaObject(void) {
    if (g_igLuaGlue_metaObject[0] == 0) {
        g_igLuaGlue_metaObject[0] = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igLuaGlue_metaObject[0];
}

igMetaObject *igLuaGlue_GetMetaObject(void)
{
    igMetaObject *meta = g_igLuaGlue_metaObject[0];
    if (!meta || isRegistered(meta) == false)
        igLuaGlue_EnsureRegistered();
    return g_igLuaGlue_metaObject[0];
}

int igLuaGlue_GetVTable(void) {
    ObjectImage glue;

    igObject_InitHeader(&glue);
    glue.vtable = g_igLuaGlue_vtable;
    return *(int *)((char *)&glue + g_objectSystem[0]->vtableOffset);
}

void igLuaGlue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLuaGlue_Register);
}

void *igLuaGlue_Register(void) {
    LuaLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLuaGlue_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLuaGlue_GetMetaObject,
        igLuaGlue_className,
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
