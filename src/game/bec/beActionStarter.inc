igMetaObject *g_beActionStarter_metaObject;

beActionStarter *beActionStarter_CreateInstance(int allocator) {
    beActionStarter_EnsureRegistered();
    return (beActionStarter *)igMetaObject_CreateInstance(g_beActionStarter_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beActionStarter_GetOrCreateMetaObject(void) {
    if (g_beActionStarter_metaObject == 0) {
        g_beActionStarter_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beActionStarter_metaObject;
}

void *beActionStarter_GetMetaObject(void) {
    igMetaObject *g = g_beActionStarter_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beActionStarter_EnsureRegistered();
    }
    return g_beActionStarter_metaObject;
}

int beActionStarter_GetVTable(void) {
    beActionStarter obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beActionStarter_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beActionStarter_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beActionStarter_Register);
}

CallbackArray *beActionStarter_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beActionStarter_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beActionStarter_GetMetaObjectFunction,
        "beActionStarter",
        0x20, /* instance size */
        beActionStarter_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beActionStarter_GetMetaObjectFunction(void)
{
    beActionStarter_GetMetaObject();
}

