igMetaObject *g_igIntListList_metaObject;

igMetaObject *igIntListList_GetOrCreateMetaObject(void) {
    if (g_igIntListList_metaObject == 0) {
        g_igIntListList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igIntListList_metaObject;
}

igMetaObject *igIntListList_GetMetaObject(void)
{
    igMetaObject *g = g_igIntListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igIntListList_EnsureRegistered();
    return g_igIntListList_metaObject;
}

int igIntListList_GetVTable(void) {
    igIntListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igIntListList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igIntListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igIntListList_Register);
}

static igMetaObjectCallback g_igIntListList_callbackList[] = { igIntList_EnsureRegistered, 0 };

CallbackArray *igIntListList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igIntListList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igIntListList_GetMetaObjectFunction,
        "igIntListList",
        0x14,
        igIntListList_GetVTable,
        0,
        0,
        g_igIntListList_callbackList
    );
}

void igIntListList_GetMetaObjectFunction(void) {
    igIntListList_GetMetaObject();
}

