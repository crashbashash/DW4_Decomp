igMetaObject *g_beMessengerDelayList_metaObject;

igMetaObject *beMessengerDelayList_GetOrCreateMetaObject(void) {
    if (g_beMessengerDelayList_metaObject == 0) {
        g_beMessengerDelayList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessengerDelayList_metaObject;
}

igMetaObject *beMessengerDelayList_GetMetaObject(void)
{
    igMetaObject *g = g_beMessengerDelayList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beMessengerDelayList_EnsureRegistered();
    return g_beMessengerDelayList_metaObject;
}

int beMessengerDelayList_GetVTable(void) {
    beMessengerDelayList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMessengerDelayList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beMessengerDelayList_EnsureRegistered(void)
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
        beMessengerDelayList_GetMetaObjectFunction,
        "beMessengerDelayList",
        0x14, /* instance size */
        beMessengerDelayList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerDelayList_callbackList /* callback list */
    );
}

void beMessengerDelayList_GetMetaObjectFunction(void)
{
    beMessengerDelayList_GetMetaObject();
}

