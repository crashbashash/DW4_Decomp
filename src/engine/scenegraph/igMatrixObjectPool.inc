igMetaObject *g_igMatrixObjectPool_metaObject;

igMetaObject *FUN_00199cd0(void) {
    if (g_igMatrixObjectPool_metaObject == 0) {
        g_igMatrixObjectPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMatrixObjectPool_metaObject;
}

igMetaObject *igMatrixObjectPool_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199db0();
    return g_igMatrixObjectPool_metaObject;
}

int igMatrixObjectPool_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&g_igMatrixObjectPool_vtable[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00199db0(void)
{
    igMetaObject_RunStaticInit(igMatrixObjectPool_Register);
}

static igMetaObjectCallback g_igMatrixObjectPool_callbackList[] = { FUN_001e4d30, 0 };

void igMatrixObjectPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixObjectPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igMatrixObjectPool_GetMetaObject,
        "igMatrixObjectPool",
        0x20, /* instance size */
        igMatrixObjectPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrixObjectPool_callbackList /* callback list */
    );
}

void thunk_igMatrixObjectPool_GetMetaObject(void) {
    igMatrixObjectPool_GetMetaObject();
}

