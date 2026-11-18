igMetaObject *g_igRenderPackageList_metaObject;

igMetaObject *FUN_001977c0(void) {
    if (g_igRenderPackageList_metaObject == 0) {
        g_igRenderPackageList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRenderPackageList_metaObject;
}

igMetaObject *igRenderPackageList_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackageList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001978a0();
    return g_igRenderPackageList_metaObject;
}

int igRenderPackageList_GetVTable(void) {
    struct Obj_197860 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igRenderPackageList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_001978a0(void)
{
    igMetaObject_RunStaticInit(igRenderPackageList_Register);
}

static igMetaObjectCallback g_igRenderPackageList_callbackList[] = { FUN_00197cc0, 0 };

CallbackArray *igRenderPackageList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRenderPackageList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igRenderPackageList_GetMetaObject,
        "igRenderPackageList",
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

