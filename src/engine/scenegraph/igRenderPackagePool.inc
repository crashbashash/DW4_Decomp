igMetaObject *g_igRenderPackagePool_metaObject;

igMetaObject *igRenderPackagePool_GetOrCreateMetaObject(void) {
    if (g_igRenderPackagePool_metaObject == 0) {
        g_igRenderPackagePool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRenderPackagePool_metaObject;
}

igMetaObject *igRenderPackagePool_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderPackagePool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderPackagePool_EnsureRegistered();
    return g_igRenderPackagePool_metaObject;
}

int igRenderPackagePool_GetVTable(void) {
    struct Obj_1979d0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igRenderPackagePool_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igRenderPackagePool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderPackagePool_Register);
}

static igMetaObjectCallback g_igRenderPackagePool_callbackList[] = { igRenderPackage_EnsureRegistered, 0 };

CallbackArray *igRenderPackagePool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRenderPackagePool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igRenderPackagePool_GetMetaObjectFunction,
        "igRenderPackagePool",
        0x20, /* instance size */
        igRenderPackagePool_GetVTable,
        0,
        0, /* extra callback item */
        g_igRenderPackagePool_callbackList /* callback list */
    );
}

void igRenderPackagePool_GetMetaObjectFunction(void) {
    igRenderPackagePool_GetMetaObject();
}

igMetaObject *igObjectPool_GetPublishedMetaObject(void) {
    return g_igObjectPool_metaObject;
}

