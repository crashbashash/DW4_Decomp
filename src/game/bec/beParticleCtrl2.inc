igMetaObject *g_beParticleCtrl2_metaObject;

void beParticleCtrl2_CreateInstance(int allocator) {
    beParticleCtrl2_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588510, allocator);
}

igMetaObject *beParticleCtrl2_GetOrCreateMetaObject(void) {
    if (g_beParticleCtrl2_metaObject == 0) {
        g_beParticleCtrl2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beParticleCtrl2_metaObject;
}

void *beParticleCtrl2_GetMetaObject(void) {
    igMetaObject *g = g_beParticleCtrl2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beParticleCtrl2_EnsureRegistered();
    }
    return g_beParticleCtrl2_metaObject;
}

int beParticleCtrl2_GetVTable(void) {
    beParticleCtrl2 obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beParticleCtrl2_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beParticleCtrl2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beParticleCtrl2_Register);
}

void *beParticleCtrl2_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beParticleCtrl2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beParticleCtrl2_GetMetaObjectFunction,
        "beParticleCtrl2",
        0x20, /* instance size */
        beParticleCtrl2_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beParticleCtrl2_GetMetaObjectFunction(void)
{
    beParticleCtrl2_GetMetaObject();
}

