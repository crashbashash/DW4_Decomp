igMetaObject *g_beNumberCtrl_metaObject;

beNumberCtrl *beNumberCtrl_CreateInstance(int allocator) {
    beNumberCtrl_EnsureRegistered();
    return (beNumberCtrl *)igMetaObject_CreateInstance(g_beNumberCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNumberCtrl_GetOrCreateMetaObject(void) {
    if (g_beNumberCtrl_metaObject == 0) {
        g_beNumberCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNumberCtrl_metaObject;
}

void *beNumberCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beNumberCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNumberCtrl_EnsureRegistered();
    }
    return g_beNumberCtrl_metaObject;
}

int beNumberCtrl_GetVTable(void) {
    beNumberCtrl obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beNumberCtrl_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beNumberCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumberCtrl_Register);
}

CallbackArray *beNumberCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumberCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNumberCtrl_GetMetaObjectFunction,
        "beNumberCtrl",
        0x20, /* instance size */
        beNumberCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNumberCtrl_GetMetaObjectFunction(void)
{
    beNumberCtrl_GetMetaObject();
}

