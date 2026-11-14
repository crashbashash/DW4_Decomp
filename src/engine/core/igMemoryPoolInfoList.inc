igMetaObject *igMemoryPoolInfoList_GetOrCreateMetaObject(void) {
    if (g_igMemoryPoolInfoList_metaObject[0] == 0) {
        g_igMemoryPoolInfoList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMemoryPoolInfoList_metaObject[0];
}

igMetaObject *igMemoryPoolInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryPoolInfoList_EnsureRegistered();
    return g_igMemoryPoolInfoList_metaObject[0];
}

int igMemoryPoolInfoList_GetVTable(void) {
    igMemoryPoolInfoList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&DAT_005329e0[0];
    return *(int *)((char *)&list + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void igMemoryPoolInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPoolInfoList_Register);
}

void igMemoryPoolInfoList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMemoryPoolInfoList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igMemoryPoolInfoList_GetMetaObjectFunction,
        igMemoryPoolInfoList_className,
        0x14,
        igMemoryPoolInfoList_GetVTable,
        0,
        0,
        (igMetaObjectCallback *)g_igMemoryPoolInfoList_callbackList
    );
}

void igMemoryPoolInfoList_GetMetaObjectFunction(void) {
    igMemoryPoolInfoList_GetMetaObject();
}

