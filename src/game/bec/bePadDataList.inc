igMetaObject *g_bePadDataList_metaObject;

igMetaObject *bePadDataList_GetOrCreateMetaObject(void) {
    if (g_bePadDataList_metaObject == 0) {
        g_bePadDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_bePadDataList_metaObject;
}

void *bePadDataList_GetMetaObject(void) {
    igMetaObject *g = g_bePadDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        bePadDataList_EnsureRegistered();
    }
    return g_bePadDataList_metaObject;
}

int bePadDataList_GetVTable(void) {
    bePadDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_bePadDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void bePadDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(bePadDataList_Register);
}

static igMetaObjectCallback g_bePadDataList_callbackList[] = { bePadData_EnsureRegistered, 0 };

CallbackArray *bePadDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePadDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        bePadDataList_GetMetaObjectFunction,
        "bePadDataList",
        0x14, /* instance size */
        bePadDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_bePadDataList_callbackList /* callback list */
    );
}

void bePadDataList_GetMetaObjectFunction(void)
{
    bePadDataList_GetMetaObject();
}

