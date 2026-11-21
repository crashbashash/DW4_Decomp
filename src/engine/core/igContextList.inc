igMetaObject *g_igContextList_metaObject;

void *igContextList_Create(int pool) {
    igContextList_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igContextList_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igContextList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextList_EnsureRegistered();
    return g_igContextList_metaObject;
}

int igContextList_GetVTable(void) {
    igContextList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igContextList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igContextList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igContextList_Register);
}

static igMetaObjectCallback g_igContextList_callbackList[] = { Gap::Core::igContext::arkRegister, 0 };

CallbackArray *igContextList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igContextList_metaObject,
        Gap::Core::igNonRefCountedObjectList::arkRegisterInternal,
        (igMetaObjectGetFunction)Gap::Core::igNonRefCountedObjectList::getClassMeta,
        igContextList_GetMetaObjectFunction,
        "igContextList",
        0x14,
        igContextList_GetVTable,
        0,
        0,
        g_igContextList_callbackList
    );
}

void igContextList_GetMetaObjectFunction(void) {
    igContextList_GetMetaObject();
}

