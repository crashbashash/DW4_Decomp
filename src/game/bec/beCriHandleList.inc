igMetaObject *g_beCriHandleList_metaObject;

igMetaObject *beCriHandleList_GetOrCreateMetaObject(void) {
    if (g_beCriHandleList_metaObject == 0) {
        g_beCriHandleList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beCriHandleList_metaObject;
}

void *beCriHandleList_GetMetaObject(void) {
    igMetaObject *g = g_beCriHandleList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCriHandleList_EnsureRegistered();
    }
    return g_beCriHandleList_metaObject;
}

int beCriHandleList_GetVTable(void) {
    beCriHandleList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beCriHandleList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beCriHandleList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriHandleList_Register);
}

static igMetaObjectCallback g_beCriHandleList_callbackList[] = { beCriHandle_EnsureRegistered, 0 };

CallbackArray *beCriHandleList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriHandleList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beCriHandleList_GetMetaObjectFunction,
        "beCriHandleList",
        0x14, /* instance size */
        beCriHandleList_GetVTable,
        0,
        0, /* extra callback item */
        g_beCriHandleList_callbackList /* callback list */
    );
}

void beCriHandleList_GetMetaObjectFunction(void)
{
    beCriHandleList_GetMetaObject();
}

