igMetaObject *g_igSkinList_metaObject;

igMetaObject *FUN_00197e60(void) {
    if (g_igSkinList_metaObject == 0) {
        g_igSkinList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igSkinList_metaObject;
}

igMetaObject *igSkinList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkinList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igSkinList_EnsureRegistered();
    return g_igSkinList_metaObject;
}

int igSkinList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igSkinList_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem + 916));
}

void igSkinList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igSkinList_Register);
}

static igMetaObjectCallback g_igSkinList_callbackList[] = { igSkin_EnsureRegistered, 0 };

CallbackArray *igSkinList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igSkinList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkinList_GetMetaObject,
        "igSkinList",
        0x14, /* instance size */
        igSkinList_GetVTable,
        0,
        0, /* extra callback item */
        g_igSkinList_callbackList /* callback list */
    );
}

void thunk_igSkinList_GetMetaObject(void) {
    igSkinList_GetMetaObject();
}

