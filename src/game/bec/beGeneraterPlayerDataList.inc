igMetaObject *g_beGeneraterPlayerDataList_metaObject;

igMetaObject *beGeneraterPlayerDataList_GetOrCreateMetaObject(void) {
    if (g_beGeneraterPlayerDataList_metaObject == 0) {
        g_beGeneraterPlayerDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beGeneraterPlayerDataList_metaObject;
}

void *beGeneraterPlayerDataList_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterPlayerDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGeneraterPlayerDataList_EnsureRegistered();
    }
    return g_beGeneraterPlayerDataList_metaObject;
}

int beGeneraterPlayerDataList_GetVTable(void) {
    beGeneraterPlayerDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beGeneraterPlayerDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beGeneraterPlayerDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterPlayerDataList_Register);
}

static igMetaObjectCallback g_beGeneraterPlayerDataList_callbackList[] = { beGeneraterPlayerData_EnsureRegistered, 0 };

CallbackArray *beGeneraterPlayerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterPlayerDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beGeneraterPlayerDataList_GetMetaObjectFunction,
        "beGeneraterPlayerDataList",
        0x14, /* instance size */
        beGeneraterPlayerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterPlayerDataList_callbackList /* callback list */
    );
}

void beGeneraterPlayerDataList_GetMetaObjectFunction(void)
{
    beGeneraterPlayerDataList_GetMetaObject();
}

