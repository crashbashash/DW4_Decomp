igMetaObject *g_igFloatListList_metaObject;

igMetaObject *igFloatListList_GetOrCreateMetaObject(void) {
    if (g_igFloatListList_metaObject == 0) {
        g_igFloatListList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
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
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igFloatListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFloatListList_Register);
}

static igMetaObjectCallback g_igFloatListList_callbackList[] = { igFloatList_EnsureRegistered, 0 };

void igFloatListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igFloatListList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
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

