int FUN_0044c880(void) {
    if (DAT_0058c218[0] == 0) {
        DAT_0058c218[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c218[0];
}

igMetaObject *igOnOffValueObserverList_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffValueObserverList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffValueObserverList_EnsureRegistered();
    return g_igOnOffValueObserverList_metaObject[0];
}

int igOnOffValueObserverList_GetVTable(void) {
    Obj_44c920 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_00541d00[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igOnOffValueObserverList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igOnOffValueObserverList_Register);
}

void igOnOffValueObserverList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffValueObserverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igOnOffValueObserverList_GetMetaObject,
        igOnOffValueObserverList_className,
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

