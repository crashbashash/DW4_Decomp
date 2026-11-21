igMetaObject *g_igFloatListList_metaObject;

igMetaObject *igFloatListList_GetOrCreateMetaObject(void) {
    if (g_igFloatListList_metaObject == 0) {
        g_igFloatListList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFloatListList_metaObject;
}

igMetaObject *igFloatListList_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatListList_EnsureRegistered();
    return g_igFloatListList_metaObject;
}

int igFloatListList_GetVTable(void) {
    igFloatListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igFloatListList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igFloatListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFloatListList_Register);
}

static igMetaObjectCallback g_igFloatListList_callbackList[] = { Gap::Core::igFloatList::arkRegister, 0 };

CallbackArray *igFloatListList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igFloatListList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igFloatListList_GetMetaObjectFunction,
        "igFloatListList",
        0x14,
        igFloatListList_GetVTable,
        0,
        0,
        g_igFloatListList_callbackList
    );
}

void igFloatListList_GetMetaObjectFunction(void) {
    igFloatListList_GetMetaObject();
}

