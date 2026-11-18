igMetaObject *g_beMeterCtrl_metaObject;

beMeterCtrl *beMeterCtrl_CreateInstance(int allocator) {
    beMeterCtrl_EnsureRegistered();
    return (beMeterCtrl *)igMetaObject_CreateInstance(g_beMeterCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beMeterCtrl_GetOrCreateMetaObject(void) {
    if (g_beMeterCtrl_metaObject == 0) {
        g_beMeterCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMeterCtrl_metaObject;
}

void *beMeterCtrl_GetMetaObject(void) {
    unsigned char b;
    if (g_beMeterCtrl_metaObject != 0) {
        b = (g_beMeterCtrl_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beMeterCtrl_EnsureRegistered();
done:
    return g_beMeterCtrl_metaObject;
}

int beMeterCtrl_GetVTable(void) {
    beMeterCtrl obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beMeterCtrl_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beMeterCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMeterCtrl_Register);
}

CallbackArray *beMeterCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMeterCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMeterCtrl_GetMetaObjectFunction,
        "beMeterCtrl",
        0x20, /* instance size */
        beMeterCtrl_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beMeterCtrl_GetMetaObjectFunction(void)
{
    beMeterCtrl_GetMetaObject();
}

