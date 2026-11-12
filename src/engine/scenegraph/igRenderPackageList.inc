igMetaObject *FUN_001977c0(void) {
    if (g_igRenderPackageList_metaObject[0] == 0) {
        g_igRenderPackageList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igRenderPackageList_metaObject[0];
}

igMetaObject *igRenderPackageList_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackageList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001978a0();
    return g_igRenderPackageList_metaObject[0];
}

int igRenderPackageList_GetVTable(void) {
    struct Obj_197860 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b550[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001978a0(void)
{
    igMetaObject_RunStaticInit(igRenderPackageList_Register);
}

void igRenderPackageList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igRenderPackageList_metaObject),
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igRenderPackageList_GetMetaObject,
        igRenderPackageList_className,
        0x14, /* instance size */
        igRenderPackageList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRenderPackageList_callbackList /* callback list */
    );
}

void thunk_igRenderPackageList_GetMetaObject(void) {
    igRenderPackageList_GetMetaObject();
}

