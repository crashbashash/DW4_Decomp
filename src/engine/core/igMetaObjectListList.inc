igMetaObject *g_igMetaObjectListList_metaObject;

igMetaObject *igMetaObjectListList_GetOrCreateMetaObject(void) {
    if (g_igMetaObjectListList_metaObject == 0) {
        g_igMetaObjectListList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igMetaObjectListList_metaObject;
}

igMetaObject *igMetaObjectListList_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObjectListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaObjectListList_EnsureRegistered();
    return g_igMetaObjectListList_metaObject;
}

int igMetaObjectListList_GetVTable(void) {
    igMetaObjectListList obj;

    igObject_InitHeader((igObject *)&obj);
    obj._vtable = (int)&g_igMetaObjectListList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMetaObjectListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMetaObjectListList_Register);
}

static igMetaObjectCallback g_igMetaObjectListList_callbackList[] = { igMetaObjectList_EnsureRegistered, 0 };

CallbackArray *igMetaObjectListList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMetaObjectListList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igMetaObjectListList_GetMetaObjectFunction,
        "igMetaObjectListList",
        0x14,
        igMetaObjectListList_GetVTable,
        0,
        0,
        g_igMetaObjectListList_callbackList
    );
}

void igMetaObjectListList_GetMetaObjectFunction(void) {
    igMetaObjectListList_GetMetaObject();
}

