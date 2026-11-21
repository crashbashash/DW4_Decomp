igMetaObject *g_igNonRefCountedThreadList_metaObject;

igMetaObject *igNonRefCountedThreadList_GetOrCreateMetaObject(void) {
    if (g_igNonRefCountedThreadList_metaObject == 0) {
        g_igNonRefCountedThreadList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNonRefCountedThreadList_metaObject;
}

igMetaObject *igNonRefCountedThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedThreadList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedThreadList_EnsureRegistered();
    return g_igNonRefCountedThreadList_metaObject;
}

int igNonRefCountedThreadList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igNonRefCountedThreadList_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedThreadList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedThreadList_Register);
}

static igMetaObjectCallback g_igNonRefCountedThreadList_callbackList[] = { igThread_EnsureRegistered, 0 };

CallbackArray *igNonRefCountedThreadList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igNonRefCountedThreadList_metaObject,
        Gap::Core::igNonRefCountedObjectList::arkRegisterInternal,
        (igMetaObjectGetFunction)Gap::Core::igNonRefCountedObjectList::getClassMeta,
        igNonRefCountedThreadList_GetMetaObjectFunction,
        "igNonRefCountedThreadList",
        0x14,
        igNonRefCountedThreadList_GetVTable,
        0,
        0,
        g_igNonRefCountedThreadList_callbackList
    );
}

void igNonRefCountedThreadList_GetMetaObjectFunction(void) {
    igNonRefCountedThreadList_GetMetaObject();
}

