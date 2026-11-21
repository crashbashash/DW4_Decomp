igMetaObject *g_beGeneraterDataList_metaObject;

igMetaObject *beGeneraterDataList_GetOrCreateMetaObject(void) {
    if (g_beGeneraterDataList_metaObject == 0) {
        g_beGeneraterDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beGeneraterDataList_metaObject;
}

igMetaObject *beGeneraterDataList_GetMetaObject(void) {
    if (g_beGeneraterDataList_metaObject == 0 || !isValid(g_beGeneraterDataList_metaObject)) beGeneraterDataList_EnsureRegistered();
    return g_beGeneraterDataList_metaObject;
}

int beGeneraterDataList_GetVTable(void) {
    beGeneraterDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beGeneraterDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beGeneraterDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterDataList_Register);
}

static igMetaObjectCallback g_beGeneraterDataList_callbackList[] = { beGeneraterData_EnsureRegistered, 0 };

CallbackArray *beGeneraterDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beGeneraterDataList_GetMetaObjectFunction,
        "beGeneraterDataList",
        0x14, /* instance size */
        beGeneraterDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterDataList_callbackList /* callback list */
    );
}

void beGeneraterDataList_GetMetaObjectFunction(void)
{
    beGeneraterDataList_GetMetaObject();
}

