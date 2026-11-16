igMetaObject *g_beDBManager_metaObject;

void beDBManager_CreateInstance(int allocator) {
    beDBManager_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589958, allocator);
}

igMetaObject *beDBManager_GetOrCreateMetaObject(void) {
    if (g_beDBManager_metaObject == 0) {
        g_beDBManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beDBManager_metaObject;
}

igMetaObject *beDBManager_GetMetaObject(void) {
    igMetaObject *g = g_beDBManager_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beDBManager_EnsureRegistered();
    return g_beDBManager_metaObject;
}

int beDBManager_GetVTable(void) {
    beDBManager obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beDBManager_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beDBManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDBManager_Register);
}

void *beDBManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDBManager_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beDBManager_GetMetaObjectFunction,
        "beDBManager",
        0x20, /* instance size */
        beDBManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beDBManager_GetMetaObjectFunction(void)
{
    beDBManager_GetMetaObject();
}

