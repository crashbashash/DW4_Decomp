igMetaObject *g_igMatrixObjectPool_metaObject;

igMetaObject *igMatrixObjectPool_GetOrCreateMetaObject(void) {
    if (g_igMatrixObjectPool_metaObject == 0) {
        g_igMatrixObjectPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMatrixObjectPool_metaObject;
}

igMetaObject *igMatrixObjectPool_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMatrixObjectPool_EnsureRegistered();
    return g_igMatrixObjectPool_metaObject;
}

int igMatrixObjectPool_GetVTable(void) {
    union U u;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igMatrixObjectPool_vtable[0];
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igMatrixObjectPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMatrixObjectPool_Register);
}

static igMetaObjectCallback g_igMatrixObjectPool_callbackList[] = { igMatrixObject_EnsureRegistered, 0 };

CallbackArray *igMatrixObjectPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixObjectPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igMatrixObjectPool_GetMetaObjectFunction,
        "igMatrixObjectPool",
        0x20, /* instance size */
        igMatrixObjectPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrixObjectPool_callbackList /* callback list */
    );
}

void igMatrixObjectPool_GetMetaObjectFunction(void) {
    igMatrixObjectPool_GetMetaObject();
}

