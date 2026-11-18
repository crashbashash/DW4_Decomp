igMetaObject *g_beHitLandDeliv_metaObject;

beHitLandDeliv *beHitLandDeliv_CreateInstance(int allocator) {
    beHitLandDeliv_EnsureRegistered();
    return (beHitLandDeliv *)igMetaObject_CreateInstance(g_beHitLandDeliv_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beHitLandDeliv_GetOrCreateMetaObject(void) {
    if (g_beHitLandDeliv_metaObject == 0) {
        g_beHitLandDeliv_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beHitLandDeliv_metaObject;
}

void *beHitLandDeliv_GetMetaObject(void) {
    igMetaObject *g = g_beHitLandDeliv_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beHitLandDeliv_EnsureRegistered();
    }
    return g_beHitLandDeliv_metaObject;
}

int beHitLandDeliv_GetVTable(void) {
    beHitLandDeliv obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beHitLandDeliv_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beHitLandDeliv_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beHitLandDeliv_Register);
}

CallbackArray *beHitLandDeliv_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beHitLandDeliv_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beHitLandDeliv_GetMetaObjectFunction,
        "beHitLandDeliv",
        0x20, /* instance size */
        beHitLandDeliv_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beHitLandDeliv_GetMetaObjectFunction(void)
{
    beHitLandDeliv_GetMetaObject();
}

