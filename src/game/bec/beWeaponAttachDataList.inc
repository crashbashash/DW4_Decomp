igMetaObject *g_beWeaponAttachDataList_metaObject;

void beWeaponAttachDataList_Create(int allocator) {
    beWeaponAttachDataList_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x587A78, allocator);
}

igMetaObject *beWeaponAttachDataList_GetOrCreateMetaObject(void) {
    if (g_beWeaponAttachDataList_metaObject == 0) {
        g_beWeaponAttachDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beWeaponAttachDataList_metaObject;
}

igMetaObject *beWeaponAttachDataList_GetMetaObject(void)
{
    igMetaObject *g = g_beWeaponAttachDataList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beWeaponAttachDataList_EnsureRegistered();
    return g_beWeaponAttachDataList_metaObject;
}

int beWeaponAttachDataList_GetVTable(void) {
    beWeaponAttachDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beWeaponAttachDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void beWeaponAttachDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeaponAttachDataList_Register);
}

static igMetaObjectCallback g_beWeaponAttachDataList_callbackList[] = { beWeaponAttachData_EnsureRegistered, 0 };

void *beWeaponAttachDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeaponAttachDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beWeaponAttachDataList_GetMetaObjectFunction,
        "beWeaponAttachDataList",
        0x14, /* instance size */
        beWeaponAttachDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beWeaponAttachDataList_callbackList /* callback list */
    );
}

void beWeaponAttachDataList_GetMetaObjectFunction(void)
{
    beWeaponAttachDataList_GetMetaObject();
}

