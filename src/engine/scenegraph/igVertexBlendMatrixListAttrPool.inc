igMetaObject *g_igVertexBlendMatrixListAttrPool_metaObject;

igMetaObject *FUN_00199e40(void) {
    if (g_igVertexBlendMatrixListAttrPool_metaObject == 0) {
        g_igVertexBlendMatrixListAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVertexBlendMatrixListAttrPool_metaObject;
}

igMetaObject *igVertexBlendMatrixListAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixListAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199f20();
    return g_igVertexBlendMatrixListAttrPool_metaObject;
}

int igVertexBlendMatrixListAttrPool_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igVertexBlendMatrixListAttrPool_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_00199f20(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixListAttrPool_Register);
}

static igMetaObjectCallback g_igVertexBlendMatrixListAttrPool_callbackList[] = { FUN_00130a70, 0 };

CallbackArray *igVertexBlendMatrixListAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexBlendMatrixListAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixListAttrPool_GetMetaObject,
        "igVertexBlendMatrixListAttrPool",
        0x20, /* instance size */
        igVertexBlendMatrixListAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexBlendMatrixListAttrPool_callbackList /* callback list */
    );
}

void thunk_igVertexBlendMatrixListAttrPool_GetMetaObject(void) {
    igVertexBlendMatrixListAttrPool_GetMetaObject();
}

