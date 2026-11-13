igMetaObject *FUN_001999f0(void) {
    if (g_igBlendMatricesAttrPool_metaObject[0] == 0) {
        g_igBlendMatricesAttrPool_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igBlendMatricesAttrPool_metaObject[0];
}

igMetaObject *igBlendMatricesAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatricesAttrPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199ad0();
    return g_igBlendMatricesAttrPool_metaObject[0];
}

int igBlendMatricesAttrPool_GetVTable(void) {
    struct Obj_199a90 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052b190[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00199ad0(void)
{
    igMetaObject_RunStaticInit(igBlendMatricesAttrPool_Register);
}

void igBlendMatricesAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igBlendMatricesAttrPool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igBlendMatricesAttrPool_GetMetaObject,
        igBlendMatricesAttrPool_className,
        0x20, /* instance size */
        igBlendMatricesAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igBlendMatricesAttrPool_callbackList /* callback list */
    );
}

void thunk_igBlendMatricesAttrPool_GetMetaObject(void) {
    igBlendMatricesAttrPool_GetMetaObject();
}

