igMetaObject *FUN_00197e60(void) {
    if (g_igSkinList_metaObject[0] == 0) {
        g_igSkinList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igSkinList_metaObject[0];
}

igMetaObject *igSkinList_GetMetaObject(void)
{
    igMetaObject *g = g_igSkinList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00197f40();
    return g_igSkinList_metaObject[0];
}

int igSkinList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_0052b410[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00197f40(void)
{
    igMetaObject_RunStaticInit(igSkinList_Register);
}

void igSkinList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igSkinList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igSkinList_GetMetaObject,
        igSkinList_className,
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

