igMetaObject *g_igNamedObjectList_metaObject;

igMetaObject *igNamedObjectList_GetOrCreateMetaObject(void) {
    if (g_igNamedObjectList_metaObject == 0) {
        g_igNamedObjectList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNamedObjectList_metaObject;
}

igMetaObject *igNamedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNamedObjectList_EnsureRegistered();
    return g_igNamedObjectList_metaObject;
}

int igNamedObjectList_GetVTable(void) {
    igNamedObjectList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igNamedObjectList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igNamedObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNamedObjectList_Register);
}

static igMetaObjectCallback g_igNamedObjectList_callbackList[] = { igNamedObject_EnsureRegistered, 0 };

CallbackArray *igNamedObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igNamedObjectList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igNamedObjectList_GetMetaObjectFunction,
        "igNamedObjectList",
        0x14,
        igNamedObjectList_GetVTable,
        0,
        0,
        g_igNamedObjectList_callbackList
    );
}

void igNamedObjectList_GetMetaObjectFunction(void) {
    igNamedObjectList_GetMetaObject();
}

