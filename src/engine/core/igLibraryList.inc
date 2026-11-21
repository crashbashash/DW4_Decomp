igMetaObject *g_igLibraryList_metaObject;

igMetaObject *igLibraryList_GetOrCreateMetaObject(void) {
    if (g_igLibraryList_metaObject == 0) {
        g_igLibraryList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLibraryList_metaObject;
}

igMetaObject *igLibraryList_GetMetaObject(void)
{
    igMetaObject *g = g_igLibraryList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLibraryList_EnsureRegistered();
    return g_igLibraryList_metaObject;
}

int igLibraryList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igLibraryList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igLibraryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLibraryList_Register);
}

static igMetaObjectCallback g_igLibraryList_callbackList[] = { igLibrary_EnsureRegistered, 0 };

CallbackArray *igLibraryList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igLibraryList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igLibraryList_GetMetaObjectFunction,
        "igLibraryList",
        0x14,
        igLibraryList_GetVTable,
        0,
        0,
        g_igLibraryList_callbackList
    );
}

void igLibraryList_GetMetaObjectFunction(void) {
    igLibraryList_GetMetaObject();
}

