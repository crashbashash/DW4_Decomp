igMetaObject *g_igVertexBlendMatrixListAttrPool_metaObject;

igMetaObject *FUN_00199e40(void) {
    if (g_igVertexBlendMatrixListAttrPool_metaObject == 0) {
        g_igVertexBlendMatrixListAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_0052b040[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00199f20(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixListAttrPool_Register);
}

static igMetaObjectCallback g_igVertexBlendMatrixListAttrPool_callbackList[] = { FUN_00130a70, 0 };

void igVertexBlendMatrixListAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
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

