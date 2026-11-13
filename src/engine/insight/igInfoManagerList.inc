igMetaObject *FUN_00233750(void) {
    if (g_igInfoManagerList_metaObject[0] == 0) {
        g_igInfoManagerList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igInfoManagerList_metaObject[0];
}

igMetaObject *igInfoManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233830();
    return g_igInfoManagerList_metaObject[0];
}

int igInfoManagerList_GetVTable(void) {
    struct Obj_2337f0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052caf0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00233830(void)
{
    igMetaObject_RunStaticInit(igInfoManagerList_Register);
}

void igInfoManagerList_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInfoManagerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igInfoManagerList_GetMetaObject,
        igInfoManagerList_className,
        0x14, /* instance size */
        igInfoManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerList_callbackList /* callback list */
    );
}

void thunk_igInfoManagerList_GetMetaObject(void) {
    igInfoManagerList_GetMetaObject();
}

