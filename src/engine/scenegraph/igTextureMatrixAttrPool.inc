igMetaObject *FUN_00199b60(void) {
    if (g_igTextureMatrixAttrPool_metaObject[0] == 0) {
        g_igTextureMatrixAttrPool_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igTextureMatrixAttrPool_metaObject[0];
}

igMetaObject *igTextureMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureMatrixAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199c40();
    return g_igTextureMatrixAttrPool_metaObject[0];
}

int igTextureMatrixAttrPool_GetVTable(void) {
    struct Obj_199c00 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b120[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00199c40(void)
{
    igMetaObject_RunStaticInit(igTextureMatrixAttrPool_Register);
}

void igTextureMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igTextureMatrixAttrPool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igTextureMatrixAttrPool_GetMetaObject,
        igTextureMatrixAttrPool_className,
        0x20, /* instance size */
        igTextureMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureMatrixAttrPool_callbackList /* callback list */
    );
}

void thunk_igTextureMatrixAttrPool_GetMetaObject(void) {
    igTextureMatrixAttrPool_GetMetaObject();
}

