igMetaObject *g_igContextExtInfoList_metaObject;

void * igContextExtInfoList_Create(int pool) {
    igContextExtInfoList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igContextExtInfoList_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igContextExtInfoList_GetOrCreateMetaObject(void) {
    if (g_igContextExtInfoList_metaObject == 0) {
        g_igContextExtInfoList_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igContextExtInfoList_metaObject;
}

igMetaObject *igContextExtInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igContextExtInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContextExtInfoList_EnsureRegistered();
    return g_igContextExtInfoList_metaObject;
}

int igContextExtInfoList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igContextExtInfoList_vtable[0];
    off = *(int *)((char *)((*(int * *)&g_objectSystem)) + 916);
    return *(int *)((char *)tmp + off);
}

void igContextExtInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContextExtInfoList_Register);
}

static igMetaObjectCallback g_igContextExtInfoList_callbackList[] = { igContextExtInfo_EnsureRegistered, 0 };

void igContextExtInfoList_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igContextExtInfoList_metaObject,
        (igMetaObjectRegisterFunction)igObjectList_Register,
        (igMetaObjectGetFunction)igObjectList_GetPublishedMetaObject,
        igContextExtInfoList_GetMetaObjectFunction,
        "igContextExtInfoList",
        0x14,
        igContextExtInfoList_GetVTable,
        0,
        0,
        g_igContextExtInfoList_callbackList
    );
}

void igContextExtInfoList_GetMetaObjectFunction(void) {
    igContextExtInfoList_GetMetaObject();
}

