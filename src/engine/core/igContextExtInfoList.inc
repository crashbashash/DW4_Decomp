igMetaObject *g_igContextExtInfoList_metaObject;

void * igContextExtInfoList_Create(int pool) {
    igContextExtInfoList_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igContextExtInfoList_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igContextExtInfoList_GetOrCreateMetaObject(void) {
    if (g_igContextExtInfoList_metaObject == 0) {
        g_igContextExtInfoList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igContextExtInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igContextExtInfoList_Register);
}

static igMetaObjectCallback g_igContextExtInfoList_callbackList[] = { igContextExtInfo_EnsureRegistered, 0 };

CallbackArray *igContextExtInfoList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igContextExtInfoList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
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

