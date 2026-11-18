igMetaObject *g_igVertexBlendMatrixAttrPool_metaObject;

igMetaObject *igVertexBlendMatrixAttrPool_GetOrCreateMetaObject(void) {
    if (g_igVertexBlendMatrixAttrPool_metaObject == 0) {
        g_igVertexBlendMatrixAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVertexBlendMatrixAttrPool_metaObject;
}

igMetaObject *igVertexBlendMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVertexBlendMatrixAttrPool_EnsureRegistered();
    return g_igVertexBlendMatrixAttrPool_metaObject;
}

int igVertexBlendMatrixAttrPool_GetVTable(void) {
    struct Obj_19a050 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igVertexBlendMatrixAttrPool_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igVertexBlendMatrixAttrPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixAttrPool_Register);
}

static igMetaObjectCallback g_igVertexBlendMatrixAttrPool_callbackList[] = { igVertexBlendMatrixAttr_EnsureRegistered, 0 };

CallbackArray *igVertexBlendMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexBlendMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igVertexBlendMatrixAttrPool_GetMetaObjectFunction,
        "igVertexBlendMatrixAttrPool",
        0x20, /* instance size */
        igVertexBlendMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexBlendMatrixAttrPool_callbackList /* callback list */
    );
}

void igVertexBlendMatrixAttrPool_GetMetaObjectFunction(void) {
    igVertexBlendMatrixAttrPool_GetMetaObject();
}

