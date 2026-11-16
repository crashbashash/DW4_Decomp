igMetaObject *g_igBlendMatricesAttrPool_metaObject;

igMetaObject *FUN_001999f0(void) {
    if (g_igBlendMatricesAttrPool_metaObject == 0) {
        g_igBlendMatricesAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBlendMatricesAttrPool_metaObject;
}

igMetaObject *igBlendMatricesAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatricesAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199ad0();
    return g_igBlendMatricesAttrPool_metaObject;
}

int igBlendMatricesAttrPool_GetVTable(void) {
    struct Obj_199a90 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igBlendMatricesAttrPool_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_00199ad0(void)
{
    igMetaObject_RunStaticInit(igBlendMatricesAttrPool_Register);
}

static igMetaObjectCallback g_igBlendMatricesAttrPool_callbackList[] = { FUN_00139ce0, 0 };

CallbackArray *igBlendMatricesAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatricesAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igBlendMatricesAttrPool_GetMetaObject,
        "igBlendMatricesAttrPool",
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

