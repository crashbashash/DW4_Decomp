int FUN_00231790(void) {
    if (DAT_0056dae0[0] == 0) {
        DAT_0056dae0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056dae0[0];
}

igMetaObject *igMessageReceiverList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiverList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231870();
    return g_igMessageReceiverList_metaObject[0];
}

int igMessageReceiverList_GetVTable(void) {
    struct Obj_231830 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ceb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00231870(void)
{
    igMetaObject_RunStaticInit(igMessageReceiverList_Register);
}

void igMessageReceiverList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageReceiverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageReceiverList_GetMetaObject,
        igMessageReceiverList_className,
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

