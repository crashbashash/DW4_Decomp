igMetaObject *g_igRenderPackageList_metaObject;

igMetaObject *igRenderPackageList_GetOrCreateMetaObject(void) {
    if (g_igRenderPackageList_metaObject == 0) {
        g_igRenderPackageList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRenderPackageList_metaObject;
}

igMetaObject *igRenderPackageList_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackageList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderPackageList_EnsureRegistered();
    return g_igRenderPackageList_metaObject;
}

int igRenderPackageList_GetVTable(void) {
    struct Obj_197860 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igRenderPackageList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igRenderPackageList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderPackageList_Register);
}

static igMetaObjectCallback g_igRenderPackageList_callbackList[] = { igRenderPackage_EnsureRegistered, 0 };

CallbackArray *igRenderPackageList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRenderPackageList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        igRenderPackageList_GetMetaObjectFunction,
        "igRenderPackageList",
        0x14, /* instance size */
        igRenderPackageList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRenderPackageList_callbackList /* callback list */
    );
}

void igRenderPackageList_GetMetaObjectFunction(void) {
    igRenderPackageList_GetMetaObject();
}

