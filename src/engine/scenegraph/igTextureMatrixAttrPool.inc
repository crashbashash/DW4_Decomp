igMetaObject *g_igTextureMatrixAttrPool_metaObject;

igMetaObject *FUN_00199b60(void) {
    if (g_igTextureMatrixAttrPool_metaObject == 0) {
        g_igTextureMatrixAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextureMatrixAttrPool_metaObject;
}

igMetaObject *igTextureMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureMatrixAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199c40();
    return g_igTextureMatrixAttrPool_metaObject;
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

static igMetaObjectCallback g_igTextureMatrixAttrPool_callbackList[] = { FUN_001318f0, 0 };

void igTextureMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igTextureMatrixAttrPool_GetMetaObject,
        "igTextureMatrixAttrPool",
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

