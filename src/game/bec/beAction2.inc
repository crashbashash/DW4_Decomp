igMetaObject *g_beAction2_metaObject;

beAction2 *beAction2_CreateInstance(int allocator) {
    beAction2_EnsureRegistered();
    return (beAction2 *)igMetaObject_CreateInstance(g_beAction2_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beAction2_GetOrCreateMetaObject(void) {
    if (g_beAction2_metaObject == 0) {
        g_beAction2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beAction2_metaObject;
}

void *beAction2_GetMetaObject(void) {
    igMetaObject *g = g_beAction2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beAction2_EnsureRegistered();
    }
    return g_beAction2_metaObject;
}

int beAction2_GetVTable(void) {
    beAction2 obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beAction2_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beAction2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beAction2_Register);
}

CallbackArray *beAction2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beAction2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beAction2_GetMetaObjectFunction,
        "beAction2",
        0x20, /* instance size */
        beAction2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2_GetMetaObjectFunction(void)
{
    beAction2_GetMetaObject();
}

