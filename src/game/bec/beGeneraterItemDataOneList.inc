igMetaObject *g_beGeneraterItemDataOneList_metaObject;

igMetaObject *beGeneraterItemDataOneList_GetOrCreateMetaObject(void) {
    if (g_beGeneraterItemDataOneList_metaObject == 0) {
        g_beGeneraterItemDataOneList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beGeneraterItemDataOneList_metaObject;
}

void *beGeneraterItemDataOneList_GetMetaObject(void) {
    igMetaObject *g = g_beGeneraterItemDataOneList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGeneraterItemDataOneList_EnsureRegistered();
    }
    return g_beGeneraterItemDataOneList_metaObject;
}

int beGeneraterItemDataOneList_GetVTable(void) {
    beGeneraterItemDataOneList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beGeneraterItemDataOneList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beGeneraterItemDataOneList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataOneList_Register);
}

static igMetaObjectCallback g_beGeneraterItemDataOneList_callbackList[] = { beGeneraterItemDataOne_EnsureRegistered, 0 };

CallbackArray *beGeneraterItemDataOneList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterItemDataOneList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beGeneraterItemDataOneList_GetMetaObjectFunction,
        "beGeneraterItemDataOneList",
        0x14, /* instance size */
        beGeneraterItemDataOneList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterItemDataOneList_callbackList /* callback list */
    );
}

void beGeneraterItemDataOneList_GetMetaObjectFunction(void)
{
    beGeneraterItemDataOneList_GetMetaObject();
}

