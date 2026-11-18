igMetaObject *g_igProjectionMatrixAttrPool_metaObject;

igMetaObject *FUN_0019a120(void) {
    if (g_igProjectionMatrixAttrPool_metaObject == 0) {
        g_igProjectionMatrixAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igProjectionMatrixAttrPool_metaObject;
}

igMetaObject *igProjectionMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igProjectionMatrixAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a200();
    return g_igProjectionMatrixAttrPool_metaObject;
}

int igProjectionMatrixAttrPool_GetVTable(void) {
    struct Obj_19a1c0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igProjectionMatrixAttrPool_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_0019a200(void)
{
    igMetaObject_RunStaticInit(igProjectionMatrixAttrPool_Register);
}

static igMetaObjectCallback g_igProjectionMatrixAttrPool_callbackList[] = { igProjectionMatrixAttr_EnsureRegistered, 0 };

CallbackArray *igProjectionMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igProjectionMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igProjectionMatrixAttrPool_GetMetaObject,
        "igProjectionMatrixAttrPool",
        0x20, /* instance size */
        igProjectionMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igProjectionMatrixAttrPool_callbackList /* callback list */
    );
}

void thunk_igProjectionMatrixAttrPool_GetMetaObject(void) {
    igProjectionMatrixAttrPool_GetMetaObject();
}

