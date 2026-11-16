igMetaObject *g_igMessageReceiverList_metaObject;

igMetaObject *FUN_00231790(void) {
    if (g_igMessageReceiverList_metaObject == 0) {
        g_igMessageReceiverList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMessageReceiverList_metaObject;
}

igMetaObject *igMessageReceiverList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiverList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231870();
    return g_igMessageReceiverList_metaObject;
}

int igMessageReceiverList_GetVTable(void) {
    struct Obj_231830 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMessageReceiverList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void FUN_00231870(void)
{
    igMetaObject_RunStaticInit(igMessageReceiverList_Register);
}

static igMetaObjectCallback g_igMessageReceiverList_callbackList[] = { FUN_00231950, 0 };

CallbackArray *igMessageReceiverList_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageReceiverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageReceiverList_GetMetaObject,
        "igMessageReceiverList",
        0x14, /* instance size */
        igMessageReceiverList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageReceiverList_callbackList /* callback list */
    );
}

void thunk_igMessageReceiverList_GetMetaObject(void) {
    igMessageReceiverList_GetMetaObject();
}

