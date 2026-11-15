igMetaObject *g_igAABoxList_metaObject;

igMetaObject *FUN_0018a4f0(void) {
    if (g_igAABoxList_metaObject == 0) {
        g_igAABoxList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAABoxList_metaObject;
}

igMetaObject *igAABoxList_GetMetaObject(void)
{
    igMetaObject *g = g_igAABoxList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0018a5d0();
    return g_igAABoxList_metaObject;
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

static igMetaObjectCallback g_igAABoxList_callbackList[] = { FUN_0018a780, 0 };

void igAABoxList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAABoxList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAABoxList_GetMetaObject,
        "igAABoxList",
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

