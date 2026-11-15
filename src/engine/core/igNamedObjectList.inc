igMetaObject *g_igNamedObjectList_metaObject;

igMetaObject *igNamedObjectList_GetOrCreateMetaObject(void) {
    if (g_igNamedObjectList_metaObject == 0) {
        g_igNamedObjectList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igNamedObjectList_metaObject;
}

igMetaObject *igNamedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNamedObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNamedObjectList_EnsureRegistered();
    return g_igNamedObjectList_metaObject;
}

int igNamedObjectList_GetVTable(void) {
    igNamedObjectList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igNamedObjectList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igNamedObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igNamedObjectList_Register);
}

static igMetaObjectCallback g_igNamedObjectList_callbackList[] = { igNamedObject_EnsureRegistered, 0 };

void igNamedObjectList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igNamedObjectList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igNamedObjectList_GetMetaObjectFunction,
        "igNamedObjectList",
        0x14,
        igNamedObjectList_GetVTable,
        0,
        0,
        g_igNamedObjectList_callbackList
    );
}

void igNamedObjectList_GetMetaObjectFunction(void) {
    igNamedObjectList_GetMetaObject();
}

