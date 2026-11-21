igMetaObject *g_beGeneraterItemDataList_metaObject;

igMetaObject *beGeneraterItemDataList_GetOrCreateMetaObject(void) {
    if (g_beGeneraterItemDataList_metaObject == 0) {
        g_beGeneraterItemDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beGeneraterItemDataList_metaObject;
}

void *beGeneraterItemDataList_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterItemDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGeneraterItemDataList_EnsureRegistered();
    }
    return g_beGeneraterItemDataList_metaObject;
}

int beGeneraterItemDataList_GetVTable(void) {
    beGeneraterItemDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beGeneraterItemDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beGeneraterItemDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataList_Register);
}

static igMetaObjectCallback g_beGeneraterItemDataList_callbackList[] = { beGeneraterItemData_EnsureRegistered, 0 };

CallbackArray *beGeneraterItemDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterItemDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beGeneraterItemDataList_GetMetaObjectFunction,
        "beGeneraterItemDataList",
        0x14, /* instance size */
        beGeneraterItemDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterItemDataList_callbackList /* callback list */
    );
}

void beGeneraterItemDataList_GetMetaObjectFunction(void)
{
    beGeneraterItemDataList_GetMetaObject();
}

