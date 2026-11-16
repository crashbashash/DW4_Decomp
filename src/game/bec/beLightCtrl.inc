igMetaObject *g_beLightCtrl_metaObject;

void beLightCtrl_CreateInstance(int allocator) {
    beLightCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589258, allocator);
}

igMetaObject *beLightCtrl_GetOrCreateMetaObject(void) {
    if (g_beLightCtrl_metaObject == 0) {
        g_beLightCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLightCtrl_metaObject;
}

void *beLightCtrl_GetMetaObject(void) {
    unsigned char b;
    if (g_beLightCtrl_metaObject != 0) {
        b = (g_beLightCtrl_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beLightCtrl_EnsureRegistered();
done:
    return g_beLightCtrl_metaObject;
}

int beLightCtrl_GetVTable(void) {
    beLightCtrl obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beLightCtrl_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beLightCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLightCtrl_Register);
}

void *beLightCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLightCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beLightCtrl_GetMetaObjectFunction,
        "beLightCtrl",
        0x20, /* instance size */
        beLightCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLightCtrl_GetMetaObjectFunction(void)
{
    beLightCtrl_GetMetaObject();
}

