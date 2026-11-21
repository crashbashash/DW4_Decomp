igMetaObject *g_beWeaponSeqDataList_metaObject;

igMetaObject *beWeaponSeqDataList_GetOrCreateMetaObject(void) {
    if (g_beWeaponSeqDataList_metaObject == 0) {
        g_beWeaponSeqDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beWeaponSeqDataList_metaObject;
}

void *beWeaponSeqDataList_GetMetaObject(void) {
    igMetaObject *g = g_beWeaponSeqDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beWeaponSeqDataList_EnsureRegistered();
    }
    return g_beWeaponSeqDataList_metaObject;
}

int beWeaponSeqDataList_GetVTable(void) {
    beWeaponSeqDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beWeaponSeqDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beWeaponSeqDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beWeaponSeqDataList_Register);
}

static igMetaObjectCallback g_beWeaponSeqDataList_callbackList[] = { beWeaponSeqData_EnsureRegistered, 0 };

CallbackArray *beWeaponSeqDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beWeaponSeqDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beWeaponSeqDataList_GetMetaObjectFunction,
        "beWeaponSeqDataList",
        0x14, /* instance size */
        beWeaponSeqDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beWeaponSeqDataList_callbackList /* callback list */
    );
}

void beWeaponSeqDataList_GetMetaObjectFunction(void)
{
    beWeaponSeqDataList_GetMetaObject();
}

