igMetaObject *FUN_0018a4f0(void) {
    if (g_igAABoxList_metaObject[0] == 0) {
        g_igAABoxList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAABoxList_metaObject[0];
}

igMetaObject *igAABoxList_GetMetaObject(void)
{
    igMetaObject *g = g_igAABoxList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0018a5d0();
    return g_igAABoxList_metaObject[0];
}

int igAABoxList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527840[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0018a5d0(void)
{
    igMetaObject_RunStaticInit(igAABoxList_Register);
}

void igAABoxList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAABoxList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAABoxList_GetMetaObject,
        igAABoxList_className,
        0x14, /* instance size */
        igAABoxList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAABoxList_callbackList /* callback list */
    );
}

void thunk_igAABoxList_GetMetaObject(void) {
    igAABoxList_GetMetaObject();
}

