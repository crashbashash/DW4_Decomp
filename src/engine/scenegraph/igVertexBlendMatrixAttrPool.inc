igMetaObject *g_igVertexBlendMatrixAttrPool_metaObject;

igMetaObject *FUN_00199fb0(void) {
    if (g_igVertexBlendMatrixAttrPool_metaObject == 0) {
        g_igVertexBlendMatrixAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igVertexBlendMatrixAttrPool_metaObject;
}

igMetaObject *igVertexBlendMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a090();
    return g_igVertexBlendMatrixAttrPool_metaObject;
}

int igVertexBlendMatrixAttrPool_GetVTable(void) {
    struct Obj_19a050 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igVertexBlendMatrixAttrPool_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0019a090(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixAttrPool_Register);
}

static igMetaObjectCallback g_igVertexBlendMatrixAttrPool_callbackList[] = { FUN_00130cf0, 0 };

void igVertexBlendMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igVertexBlendMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixAttrPool_GetMetaObject,
        "igVertexBlendMatrixAttrPool",
        0x20, /* instance size */
        igVertexBlendMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexBlendMatrixAttrPool_callbackList /* callback list */
    );
}

void thunk_igVertexBlendMatrixAttrPool_GetMetaObject(void) {
    igVertexBlendMatrixAttrPool_GetMetaObject();
}

