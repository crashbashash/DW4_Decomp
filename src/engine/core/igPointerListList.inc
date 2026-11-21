igMetaObject *g_igPointerListList_metaObject;

igMetaObject *igPointerListList_GetOrCreateMetaObject(void) {
    if (g_igPointerListList_metaObject == 0) {
        g_igPointerListList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igPointerListList_metaObject;
}

igMetaObject *igPointerListList_GetMetaObject(void)
{
    igMetaObject *g = g_igPointerListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPointerListList_EnsureRegistered();
    return g_igPointerListList_metaObject;
}

int igPointerListList_GetVTable(void) {
    igPointerListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igPointerListList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igPointerListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPointerListList_Register);
}

static igMetaObjectCallback g_igPointerListList_callbackList[] = { Gap::Core::igPointerList::arkRegister, 0 };

CallbackArray *igPointerListList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPointerListList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igPointerListList_GetMetaObjectFunction,
        "igPointerListList",
        0x14,
        igPointerListList_GetVTable,
        0,
        0,
        g_igPointerListList_callbackList
    );
}

void igPointerListList_GetMetaObjectFunction(void) {
    igPointerListList_GetMetaObject();
}

