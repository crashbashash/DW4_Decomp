igMetaObject *g_beMessengerArgDataList_metaObject;

igMetaObject *beMessengerArgDataList_GetOrCreateMetaObject(void) {
    if (g_beMessengerArgDataList_metaObject == 0) {
        g_beMessengerArgDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMessengerArgDataList_metaObject;
}

igMetaObject *beMessengerArgDataList_GetMetaObject(void) {
    igMetaObject *g = g_beMessengerArgDataList_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    beMessengerArgDataList_EnsureRegistered();
done:
    return g_beMessengerArgDataList_metaObject;
}

int beMessengerArgDataList_GetVTable(void) {
    beMessengerArgDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beMessengerArgDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beMessengerArgDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMessengerArgDataList_Register);
}

static igMetaObjectCallback g_beMessengerArgDataList_callbackList[] = { beMessengerArgData_EnsureRegistered, 0 };

void *beMessengerArgDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMessengerArgDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMessengerArgDataList_GetMetaObjectFunction,
        "beMessengerArgDataList",
        0x14, /* instance size */
        beMessengerArgDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMessengerArgDataList_callbackList /* callback list */
    );
}

void beMessengerArgDataList_GetMetaObjectFunction(void)
{
    beMessengerArgDataList_GetMetaObject();
}

