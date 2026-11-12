igMetaObject *FUN_003587c0(void) {
    if (g_beMessengerDelayList_metaObject[0] == 0) {
        g_beMessengerDelayList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beMessengerDelayList_metaObject[0];
}

igMetaObject *FUN_00358810(void)
{
    igMetaObject *g = g_beMessengerDelayList_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003588a0();
    return g_beMessengerDelayList_metaObject[0];
}

int beMessengerDelayList_GetVTable(void) {
    struct Obj_358860 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536dd0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003588a0(void)
{
    igMetaObject_RunStaticInit(beMessengerDelayList_Register);
}

void *beMessengerDelayList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMessengerDelayList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerDelayList_GetMetaObject,
        beMessengerDelayList_className,
        0x14, /* instance size */
        beMessengerDelayList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerDelayList_callbackList /* callback list */
    );
}

void beMessengerDelayList_GetMetaObject(void)
{
    FUN_00358810();
}

