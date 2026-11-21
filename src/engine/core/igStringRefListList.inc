igMetaObject *g_igStringRefListList_metaObject;

igMetaObject *igStringRefListList_GetOrCreateMetaObject(void) {
    if (g_igStringRefListList_metaObject == 0) {
        g_igStringRefListList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igStringRefListList_metaObject;
}

igMetaObject *igStringRefListList_GetMetaObject(void)
{
    igMetaObject *g = g_igStringRefListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igStringRefListList_EnsureRegistered();
    return g_igStringRefListList_metaObject;
}

int igStringRefListList_GetVTable(void) {
    igStringRefListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igStringRefListList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igStringRefListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igStringRefListList_Register);
}

static igMetaObjectCallback g_igStringRefListList_callbackList[] = { igStringRefList_EnsureRegistered, 0 };

CallbackArray *igStringRefListList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igStringRefListList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igStringRefListList_GetMetaObjectFunction,
        "igStringRefListList",
        0x14,
        igStringRefListList_GetVTable,
        0,
        0,
        g_igStringRefListList_callbackList
    );
}

void igStringRefListList_GetMetaObjectFunction(void) {
    igStringRefListList_GetMetaObject();
}

