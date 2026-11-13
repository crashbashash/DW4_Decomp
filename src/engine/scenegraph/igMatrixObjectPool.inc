igMetaObject *FUN_00199cd0(void) {
    if (g_igMatrixObjectPool_metaObject[0] == 0) {
        g_igMatrixObjectPool_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMatrixObjectPool_metaObject[0];
}

igMetaObject *igMatrixObjectPool_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectPool_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00199db0();
    return g_igMatrixObjectPool_metaObject[0];
}

int igMatrixObjectPool_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052b0b0[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00199db0(void)
{
    igMetaObject_RunStaticInit(igMatrixObjectPool_Register);
}

void igMatrixObjectPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMatrixObjectPool_metaObject),
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igMatrixObjectPool_GetMetaObject,
        igMatrixObjectPool_className,
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

