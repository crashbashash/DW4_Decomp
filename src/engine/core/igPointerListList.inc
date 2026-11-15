igMetaObject *g_igPointerListList_metaObject;

igMetaObject *igPointerListList_GetOrCreateMetaObject(void) {
    if (g_igPointerListList_metaObject == 0) {
        g_igPointerListList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
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
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igPointerListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPointerListList_Register);
}

static igMetaObjectCallback g_igPointerListList_callbackList[] = { igPointerList_EnsureRegistered, 0 };

void igPointerListList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igPointerListList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
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

