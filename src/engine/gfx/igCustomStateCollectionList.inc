igMetaObject *g_igCustomStateCollectionList_metaObject;

int igCustomStateCollectionList_Create(int arg0) {
    igCustomStateCollectionList_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igCustomStateCollectionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *igCustomStateCollectionList_GetOrCreateMetaObject(void) {
    if (g_igCustomStateCollectionList_metaObject == 0) {
        g_igCustomStateCollectionList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCustomStateCollectionList_metaObject;
}

igMetaObject *igCustomStateCollectionList_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateCollectionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCustomStateCollectionList_EnsureRegistered();
    return g_igCustomStateCollectionList_metaObject;
}

int igCustomStateCollectionList_GetVTable(void) {
    struct Obj_14eee0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCustomStateCollectionList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igCustomStateCollectionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCustomStateCollectionList_Register);
}

static igMetaObjectCallback g_igCustomStateCollectionList_callbackList[] = { igCustomStateCollection_EnsureRegistered, 0 };

CallbackArray *igCustomStateCollectionList_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCustomStateCollectionList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igCustomStateCollectionList_GetMetaObjectFunction,
        "igCustomStateCollectionList",
        0x14, /* instance size */
        igCustomStateCollectionList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCustomStateCollectionList_callbackList /* callback list */
    );
}

void igCustomStateCollectionList_GetMetaObjectFunction(void) {
    igCustomStateCollectionList_GetMetaObject();
}

