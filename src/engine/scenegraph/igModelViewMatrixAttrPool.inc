igMetaObject *g_igModelViewMatrixAttrPool_metaObject;

igMetaObject *FUN_0019a400(void) {
    if (g_igModelViewMatrixAttrPool_metaObject == 0) {
        g_igModelViewMatrixAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igModelViewMatrixAttrPool_metaObject;
}

igMetaObject *igModelViewMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019a4e0();
    return g_igModelViewMatrixAttrPool_metaObject;
}

int igModelViewMatrixAttrPool_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igModelViewMatrixAttrPool_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_0019a4e0(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixAttrPool_Register);
}

static igMetaObjectCallback g_igModelViewMatrixAttrPool_callbackList[] = { igModelViewMatrixAttr_EnsureRegistered, 0 };

CallbackArray *igModelViewMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igModelViewMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igModelViewMatrixAttrPool_GetMetaObject,
        "igModelViewMatrixAttrPool",
        0x20, /* instance size */
        igModelViewMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixAttrPool_callbackList /* callback list */
    );
}

void thunk_igModelViewMatrixAttrPool_GetMetaObject(void) {
    igModelViewMatrixAttrPool_GetMetaObject();
}

