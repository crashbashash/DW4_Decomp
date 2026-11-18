igMetaObject *g_igModelViewMatrixAttrPool_metaObject;

igMetaObject *igModelViewMatrixAttrPool_GetOrCreateMetaObject(void) {
    if (g_igModelViewMatrixAttrPool_metaObject == 0) {
        g_igModelViewMatrixAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igModelViewMatrixAttrPool_metaObject;
}

igMetaObject *igModelViewMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igModelViewMatrixAttrPool_EnsureRegistered();
    return g_igModelViewMatrixAttrPool_metaObject;
}

int igModelViewMatrixAttrPool_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igModelViewMatrixAttrPool_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igModelViewMatrixAttrPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixAttrPool_Register);
}

static igMetaObjectCallback g_igModelViewMatrixAttrPool_callbackList[] = { igModelViewMatrixAttr_EnsureRegistered, 0 };

CallbackArray *igModelViewMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igModelViewMatrixAttrPool_GetMetaObjectFunction,
        "igModelViewMatrixAttrPool",
        0x20, /* instance size */
        igModelViewMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixAttrPool_callbackList /* callback list */
    );
}

void igModelViewMatrixAttrPool_GetMetaObjectFunction(void) {
    igModelViewMatrixAttrPool_GetMetaObject();
}

