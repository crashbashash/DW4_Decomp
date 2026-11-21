igMetaObject *g_igMemoryFileEntryList_metaObject;

int igMemoryFileEntryList_Create(int pool) {
    igMemoryFileEntryList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igMemoryFileEntryList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igMemoryFileEntryList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFileEntryList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryFileEntryList_EnsureRegistered();
    return g_igMemoryFileEntryList_metaObject;
}

int igMemoryFileEntryList_GetVTable(void) {
    igMemoryFileEntryList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igMemoryFileEntryList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igMemoryFileEntryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMemoryFileEntryList_Register);
}

static igMetaObjectCallback g_igMemoryFileEntryList_callbackList[] = { igMemoryFileEntry_EnsureRegistered, 0 };

CallbackArray *igMemoryFileEntryList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMemoryFileEntryList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igMemoryFileEntryList_GetMetaObjectFunction,
        "igMemoryFileEntryList",
        0x14,
        igMemoryFileEntryList_GetVTable,
        0,
        0,
        g_igMemoryFileEntryList_callbackList
    );
}

void igMemoryFileEntryList_GetMetaObjectFunction(void) {
    igMemoryFileEntryList_GetMetaObject();
}

