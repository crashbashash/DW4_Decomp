igMetaObject *g_igCustomStateCollectionList_metaObject;

int FUN_0014ee00(int arg0) {
    FUN_0014ef20();
    return (int)igMetaObject_CreateInstance(g_igCustomStateCollectionList_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *FUN_0014ee40(void) {
    if (g_igCustomStateCollectionList_metaObject == 0) {
        g_igCustomStateCollectionList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCustomStateCollectionList_metaObject;
}

igMetaObject *igCustomStateCollectionList_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomStateCollectionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014ef20();
    return g_igCustomStateCollectionList_metaObject;
}

int igCustomStateCollectionList_GetVTable(void) {
    struct Obj_14eee0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCustomStateCollectionList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_0014ef20(void)
{
    igMetaObject_RunStaticInit(igCustomStateCollectionList_Register);
}

static igMetaObjectCallback g_igCustomStateCollectionList_callbackList[] = { FUN_0014f0c0, 0 };

CallbackArray *igCustomStateCollectionList_Register(void) {
    FUN_00149bc0();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCustomStateCollectionList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCustomStateCollectionList_GetMetaObject,
        "igCustomStateCollectionList",
        0x14, /* instance size */
        igCustomStateCollectionList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCustomStateCollectionList_callbackList /* callback list */
    );
}

void thunk_igCustomStateCollectionList_GetMetaObject(void) {
    igCustomStateCollectionList_GetMetaObject();
}

