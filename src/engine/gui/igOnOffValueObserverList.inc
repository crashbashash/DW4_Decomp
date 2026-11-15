igMetaObject *g_igOnOffValueObserverList_metaObject;

igMetaObject *FUN_0044c880(void) {
    if (g_igOnOffValueObserverList_metaObject == 0) {
        g_igOnOffValueObserverList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igOnOffValueObserverList_metaObject;
}

igMetaObject *igOnOffValueObserverList_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserverList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffValueObserverList_EnsureRegistered();
    return g_igOnOffValueObserverList_metaObject;
}

int igOnOffValueObserverList_GetVTable(void) {
    Obj_44c920 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00541d00[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igOnOffValueObserverList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOnOffValueObserverList_Register);
}

static igMetaObjectCallback g_igOnOffValueObserverList_callbackList[] = { igOnOffValueObserver_EnsureRegistered, 0 };

void igOnOffValueObserverList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOnOffValueObserverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igOnOffValueObserverList_GetMetaObject,
        "igOnOffValueObserverList",
        0x14, /* instance size */
        igOnOffValueObserverList_GetVTable,
        0,
        0, /* extra callback item */
        g_igOnOffValueObserverList_callbackList /* callback list */
    );
}

void thunk_igOnOffValueObserverList_GetMetaObject(void) {
    igOnOffValueObserverList_GetMetaObject();
}

