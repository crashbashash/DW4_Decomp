igMetaObject *g_beMessengerDelayList_metaObject;

igMetaObject *FUN_003587c0(void) {
    if (g_beMessengerDelayList_metaObject == 0) {
        g_beMessengerDelayList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessengerDelayList_metaObject;
}

igMetaObject *FUN_00358810(void)
{
    igMetaObject *g = g_beMessengerDelayList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003588a0();
    return g_beMessengerDelayList_metaObject;
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

static igMetaObjectCallback g_beMessengerDelayList_callbackList[] = { beMessengerDelay_EnsureRegistered, 0 };

void *beMessengerDelayList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerDelayList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerDelayList_GetMetaObject,
        "beMessengerDelayList",
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

