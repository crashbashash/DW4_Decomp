int FUN_00226fd0(void) {
    if (DAT_0056d928[0] == 0) {
        DAT_0056d928[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056d928[0];
}

igMetaObject *igListenerListList_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002270b0();
    return g_igListenerListList_metaObject[0];
}

int igListenerListList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c530[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_002270b0(void)
{
    igMetaObject_RunStaticInit(igListenerListList_Register);
}

void igListenerListList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igListenerListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igListenerListList_GetMetaObject,
        igListenerListList_className,
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

