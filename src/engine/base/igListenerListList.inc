igMetaObject *g_igListenerListList_metaObject;

igMetaObject *FUN_00226fd0(void) {
    if (g_igListenerListList_metaObject == 0) {
        g_igListenerListList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igListenerListList_metaObject;
}

igMetaObject *igListenerListList_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002270b0();
    return g_igListenerListList_metaObject;
}

int igListenerListList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c530[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_002270b0(void)
{
    igMetaObject_RunStaticInit(igListenerListList_Register);
}

static igMetaObjectCallback g_igListenerListList_callbackList[] = { FUN_002271d0, 0 };

void igListenerListList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igListenerListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igListenerListList_GetMetaObject,
        "igListenerListList",
        0x14, /* instance size */
        igListenerListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igListenerListList_callbackList /* callback list */
    );
}

void thunk_igListenerListList_GetMetaObject(void) {
    igListenerListList_GetMetaObject();
}

