igMetaObject *g_igVertexBlendMatrixListAttrPool_metaObject;

igMetaObject *igVertexBlendMatrixListAttrPool_GetOrCreateMetaObject(void) {
    if (g_igVertexBlendMatrixListAttrPool_metaObject == 0) {
        g_igVertexBlendMatrixListAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVertexBlendMatrixListAttrPool_metaObject;
}

igMetaObject *igVertexBlendMatrixListAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixListAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexBlendMatrixListAttrPool_EnsureRegistered();
    return g_igVertexBlendMatrixListAttrPool_metaObject;
}

int igVertexBlendMatrixListAttrPool_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igVertexBlendMatrixListAttrPool_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igVertexBlendMatrixListAttrPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixListAttrPool_Register);
}

static igMetaObjectCallback g_igVertexBlendMatrixListAttrPool_callbackList[] = { igVertexBlendMatrixListAttr_EnsureRegistered, 0 };

CallbackArray *igVertexBlendMatrixListAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexBlendMatrixListAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igVertexBlendMatrixListAttrPool_GetMetaObjectFunction,
        "igVertexBlendMatrixListAttrPool",
        0x20, /* instance size */
        igVertexBlendMatrixListAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexBlendMatrixListAttrPool_callbackList /* callback list */
    );
}

void igVertexBlendMatrixListAttrPool_GetMetaObjectFunction(void) {
    igVertexBlendMatrixListAttrPool_GetMetaObject();
}

