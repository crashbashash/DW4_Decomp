igMetaObject *FUN_0019a120(void) {
    if (g_igProjectionMatrixAttrPool_metaObject[0] == 0) {
        g_igProjectionMatrixAttrPool_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igProjectionMatrixAttrPool_metaObject[0];
}

igMetaObject *igProjectionMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igProjectionMatrixAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a200();
    return g_igProjectionMatrixAttrPool_metaObject[0];
}

int igProjectionMatrixAttrPool_GetVTable(void) {
    struct Obj_19a1c0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052af60[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0019a200(void)
{
    igMetaObject_RunStaticInit(igProjectionMatrixAttrPool_Register);
}

void igProjectionMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igProjectionMatrixAttrPool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igProjectionMatrixAttrPool_GetMetaObject,
        igProjectionMatrixAttrPool_className,
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

