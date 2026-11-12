int FUN_00228cf0(void) {
    if (DAT_0056da30[0] == 0) {
        DAT_0056da30[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056da30[0];
}

igMetaObject *igFileInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igFileInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228dd0();
    return g_igFileInfoList_metaObject[0];
}

int igFileInfoList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052c1d0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00228dd0(void)
{
    igMetaObject_RunStaticInit(igFileInfoList_Register);
}

void igFileInfoList_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFileInfoList_GetMetaObject,
        igFileInfoList_className,
        0x14, /* instance size */
        igFileInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFileInfoList_callbackList /* callback list */
    );
}

void thunk_igFileInfoList_GetMetaObject(void) {
    igFileInfoList_GetMetaObject();
}

