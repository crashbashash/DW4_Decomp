igMetaObject *g_beMessengerWorkList_metaObject;

igMetaObject *beMessengerWorkList_GetOrCreateMetaObject(void) {
    if (g_beMessengerWorkList_metaObject == 0) {
        g_beMessengerWorkList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMessengerWorkList_metaObject;
}

void *beMessengerWorkList_GetMetaObject(void) {
    igMetaObject *g = g_beMessengerWorkList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMessengerWorkList_EnsureRegistered();
    }
    return g_beMessengerWorkList_metaObject;
}

int beMessengerWorkList_GetVTable(void) {
    beMessengerWorkList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMessengerWorkList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void beMessengerWorkList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMessengerWorkList_Register);
}

static igMetaObjectCallback g_beMessengerWorkList_callbackList[] = { beMessengerWork_EnsureRegistered, 0 };

CallbackArray *beMessengerWorkList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerWorkList_GetMetaObjectFunction,
        "beMessengerWorkList",
        0x14, /* instance size */
        beMessengerWorkList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerWorkList_callbackList /* callback list */
    );
}

void beMessengerWorkList_GetMetaObjectFunction(void)
{
    beMessengerWorkList_GetMetaObject();
}

