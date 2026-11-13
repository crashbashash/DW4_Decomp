igMetaObject *FUN_002320b0(void) {
    if (g_igMessageDispatcher_metaObject[0] == 0) {
        g_igMessageDispatcher_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMessageDispatcher_metaObject[0];
}

igMetaObject *igMessageDispatcher_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageDispatcher_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00232150();
    return g_igMessageDispatcher_metaObject[0];
}

void FUN_00232150(void)
{
    igMetaObject_RunStaticInit(igMessageDispatcher_Register);
}

void igMessageDispatcher_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMessageDispatcher_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageDispatcher_GetMetaObject,
        igMessageDispatcher_className,
        8, /* instance size */
        0,
        &igMessageDispatcher_SetAbstractProxy_002321e0[0], /* post-init hook */
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMessageDispatcher_GetMetaObject(void) {
    igMessageDispatcher_GetMetaObject();
}

void FUN_002321e0(void) {
    *(int *)((char *)(g_igMessageDispatcher_metaObject[0]) + 60) = (int)(&thunk_igFilterMessageDispatcher_GetMetaObject);
}

