int FUN_00199fb0(void) {
    if (DAT_005615a0[0] == 0) {
        DAT_005615a0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005615a0[0];
}

igMetaObject *igVertexBlendMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendMatrixAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a090();
    return g_igVertexBlendMatrixAttrPool_metaObject[0];
}

int igVertexBlendMatrixAttrPool_GetVTable(void) {
    struct Obj_19a050 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052afd0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0019a090(void)
{
    igMetaObject_RunStaticInit(igVertexBlendMatrixAttrPool_Register);
}

void igVertexBlendMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igVertexBlendMatrixAttrPool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igVertexBlendMatrixAttrPool_GetMetaObject,
        igVertexBlendMatrixAttrPool_className,
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

