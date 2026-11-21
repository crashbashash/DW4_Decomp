igMetaObject *g_igInfoManagerList_metaObject;

igMetaObject *igInfoManagerList_GetOrCreateMetaObject(void) {
    if (g_igInfoManagerList_metaObject == 0) {
        g_igInfoManagerList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igInfoManagerList_metaObject;
}

igMetaObject *igInfoManagerList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManagerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInfoManagerList_EnsureRegistered();
    return g_igInfoManagerList_metaObject;
}

int igInfoManagerList_GetVTable(void) {
    struct Obj_2337f0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igInfoManagerList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igInfoManagerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInfoManagerList_Register);
}

static igMetaObjectCallback g_igInfoManagerList_callbackList[] = { igInfoManager_EnsureRegistered, 0 };

CallbackArray *igInfoManagerList_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igInfoManagerList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igInfoManagerList_GetMetaObjectFunction,
        "igInfoManagerList",
        0x14, /* instance size */
        igInfoManagerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igInfoManagerList_callbackList /* callback list */
    );
}

void igInfoManagerList_GetMetaObjectFunction(void) {
    igInfoManagerList_GetMetaObject();
}

