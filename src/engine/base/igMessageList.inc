igMetaObject *FUN_00226340(void) {
    if (g_igMessageList_metaObject[0] == 0) {
        g_igMessageList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMessageList_metaObject[0];
}

igMetaObject *igMessageList_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226420();
    return g_igMessageList_metaObject[0];
}

int igMessageList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c5a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00226420(void)
{
    igMetaObject_RunStaticInit(igMessageList_Register);
}

void igMessageList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMessageList_GetMetaObject,
        igMessageList_className,
        0x14, /* instance size */
        igMessageList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMessageList_callbackList /* callback list */
    );
}

void thunk_igMessageList_GetMetaObject(void) {
    igMessageList_GetMetaObject();
}

