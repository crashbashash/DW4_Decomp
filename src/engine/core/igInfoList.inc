igMetaObject *g_igInfoList_metaObject;

void *igInfoList_Create(int allocator) {
    igInfoList_EnsureRegistered();
    return igMetaObject_CreateInstance(g_igInfoList_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igInfoList_GetOrCreateMetaObject(void) {
    if (g_igInfoList_metaObject == 0) {
        g_igInfoList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igInfoList_metaObject;
}

igMetaObject *igInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInfoList_EnsureRegistered();
    return g_igInfoList_metaObject;
}

int igInfoList_GetVTable(void) {
    igInfoList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igInfoList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInfoList_Register);
}

static igMetaObjectCallback g_igInfoList_callbackList[] = { igInfo_EnsureRegistered, 0 };

CallbackArray *igInfoList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igInfoList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igInfoList_GetMetaObjectFunction,
        "igInfoList",
        0x14,
        igInfoList_GetVTable,
        0,
        0,
        g_igInfoList_callbackList
    );
}

void igInfoList_GetMetaObjectFunction(void) {
    igInfoList_GetMetaObject();
}

