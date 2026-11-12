igMetaObject *FUN_0036aaf0(void) {
    if (g_beBaseInfoList_metaObject[0] == 0) {
        g_beBaseInfoList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beBaseInfoList_metaObject[0];
}

igMetaObject *FUN_0036ab40(void) {
    igMetaObject *g = g_beBaseInfoList_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0036abd0();
done:
    return g_beBaseInfoList_metaObject[0];
}

int beBaseInfoList_GetVTable(void) {
    struct Obj_36ab90 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00534750[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0036abd0(void)
{
    igMetaObject_RunStaticInit(beBaseInfoList_Register);
}

void *beBaseInfoList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBaseInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beBaseInfoList_GetMetaObject,
        beBaseInfoList_className,
        0x14, /* instance size */
        beBaseInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_beBaseInfoList_callbackList /* callback list */
    );
}

void beBaseInfoList_GetMetaObject(void)
{
    FUN_0036ab40();
}

