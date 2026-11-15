igMetaObject *g_igThreadList_metaObject;

igMetaObject *igThreadList_GetOrCreateMetaObject(void) {
    if (g_igThreadList_metaObject == 0) {
        g_igThreadList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igThreadList_metaObject;
}

igMetaObject *igThreadList_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igThreadList_EnsureRegistered();
    return g_igThreadList_metaObject;
}

int igThreadList_GetVTable(void) {
    igThreadList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igThreadList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igThreadList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igThreadList_Register);
}

static igMetaObjectCallback g_igThreadList_callbackList[] = { igThread_EnsureRegistered, 0 };

void igThreadList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igThreadList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igThreadList_GetMetaObjectFunction,
        "igThreadList",
        0x14,
        igThreadList_GetVTable,
        0,
        0,
        g_igThreadList_callbackList
    );
}

void igThreadList_GetMetaObjectFunction(void) {
    igThreadList_GetMetaObject();
}

