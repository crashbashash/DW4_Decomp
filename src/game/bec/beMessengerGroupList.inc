igMetaObject *g_beMessengerGroupList_metaObject;

igMetaObject *beMessengerGroupList_GetOrCreateMetaObject(void) {
    if (g_beMessengerGroupList_metaObject == 0) {
        g_beMessengerGroupList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMessengerGroupList_metaObject;
}

void *beMessengerGroupList_GetMetaObject(void) {
    igMetaObject *g = g_beMessengerGroupList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessengerGroupList_EnsureRegistered();
    }
    return g_beMessengerGroupList_metaObject;
}

int beMessengerGroupList_GetVTable(void) {
    beMessengerGroupList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMessengerGroupList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beMessengerGroupList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMessengerGroupList_Register);
}

static igMetaObjectCallback g_beMessengerGroupList_callbackList[] = { beMessengerGroup_EnsureRegistered, 0 };

CallbackArray *beMessengerGroupList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerGroupList_GetMetaObjectFunction,
        "beMessengerGroupList",
        0x14, /* instance size */
        beMessengerGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerGroupList_callbackList /* callback list */
    );
}

void beMessengerGroupList_GetMetaObjectFunction(void)
{
    beMessengerGroupList_GetMetaObject();
}

