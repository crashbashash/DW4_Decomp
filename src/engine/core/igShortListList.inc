igMetaObject *g_igShortListList_metaObject;

igTDataList<igTDataList<short> *> *igShortListList_Create(igMemoryPoolView *pool) {
    igShortListList_EnsureRegistered();
    return (igTDataList<igTDataList<short> *> *)igMetaObject_CreateInstance(g_igShortListList_metaObject, pool);
}

igMetaObject *igShortListList_GetOrCreateMetaObject(void) {
    if (g_igShortListList_metaObject == 0) {
        g_igShortListList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igShortListList_metaObject;
}

igMetaObject *igShortListList_GetMetaObject(void)
{
    igMetaObject *g = g_igShortListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igShortListList_EnsureRegistered();
    return g_igShortListList_metaObject;
}

int igShortListList_GetVTable(void) {
    igShortListList list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igShortListList_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igShortListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShortListList_Register);
}

static igMetaObjectCallback g_igShortListList_callbackList[] = { igShortList_EnsureRegistered, 0 };

CallbackArray *igShortListList_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igShortListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igShortListList_GetMetaObjectFunction,
        "igShortListList",
        0x14,
        igShortListList_GetVTable,
        0,
        0,
        g_igShortListList_callbackList
    );
}

void igShortListList_GetMetaObjectFunction(void) {
    igShortListList_GetMetaObject();
}

