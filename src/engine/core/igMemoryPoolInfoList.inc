igMetaObject *g_igMemoryPoolInfoList_metaObject;

igMetaObject *igMemoryPoolInfoList_GetOrCreateMetaObject(void) {
    if (g_igMemoryPoolInfoList_metaObject == 0) {
        g_igMemoryPoolInfoList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMemoryPoolInfoList_metaObject;
}

igMetaObject *igMemoryPoolInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPoolInfoList_EnsureRegistered();
    return g_igMemoryPoolInfoList_metaObject;
}

int igMemoryPoolInfoList_GetVTable(void) {
    igMemoryPoolInfoList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igMemoryPoolInfoList_vtable[0];
    return *(int *)((char *)&list + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
}

void igMemoryPoolInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPoolInfoList_Register);
}

static igMetaObjectCallback g_igMemoryPoolInfoList_callbackList[] = { igMemoryPoolInfo_EnsureRegistered, 0 };

void igMemoryPoolInfoList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igMemoryPoolInfoList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igMemoryPoolInfoList_GetMetaObjectFunction,
        "igMemoryPoolInfoList",
        0x14,
        igMemoryPoolInfoList_GetVTable,
        0,
        0,
        g_igMemoryPoolInfoList_callbackList
    );
}

void igMemoryPoolInfoList_GetMetaObjectFunction(void) {
    igMemoryPoolInfoList_GetMetaObject();
}

