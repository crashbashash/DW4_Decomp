igMetaObject *g_beNDMWLoadSlotPlayer_metaObject;
igMetaField *g_beNDMWLoadSlotPlayer_connectNOMetaField;
igMetaField *g_beNDMWLoadSlotPlayer_saveDataListMetaField;
igMetaField *g_beNDMWLoadSlotPlayer_accessPlListMetaField;

beNDMWLoadSlotPlayer *beNDMWLoadSlotPlayer_Create(int allocator) {
    beNDMWLoadSlotPlayer_EnsureRegistered();
    return (beNDMWLoadSlotPlayer *)igMetaObject_CreateInstance(g_beNDMWLoadSlotPlayer_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadSlotPlayer_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadSlotPlayer_metaObject == 0) {
        g_beNDMWLoadSlotPlayer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLoadSlotPlayer_metaObject;
}

void *beNDMWLoadSlotPlayer_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSlotPlayer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadSlotPlayer_EnsureRegistered();
    }
    return g_beNDMWLoadSlotPlayer_metaObject;
}

int beNDMWLoadSlotPlayer_GetVTable(void) {
    beNDMWLoadSlotPlayer obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWLoadSlotPlayer_vtable[0];
    obj._saveDataList = 0;
    obj._accessPlList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWLoadSlotPlayer_vtable[0];
    if (&obj._accessPlList != 0) {
        igRelease((igObject *)obj._accessPlList);
    }
    if (&obj._saveDataList != 0) {
        igRelease((igObject *)obj._saveDataList);
    }
    return vtable;
}

void beNDMWLoadSlotPlayer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSlotPlayer_Register);
}

static igMetaObjectCallback g_beNDMWLoadSlotPlayer_callbackList[] = { beNDMWDegiDataList_EnsureRegistered, Gap::Core::igIntList::arkRegister, 0 };

CallbackArray *beNDMWLoadSlotPlayer_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadSlotPlayer_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadSlotPlayer_GetMetaObject,
        "beNDMWLoadSlotPlayer",
        0x14, /* instance size */
        beNDMWLoadSlotPlayer_GetVTable,
        beNDMWLoadSlotPlayer_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadSlotPlayer_callbackList /* callback list */
    );
}

void beNDMWLoadSlotPlayer_GetMetaObject(void)
{
    beNDMWLoadSlotPlayer_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadSlotPlayer_ctorTable[] = {
    igIntMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWLoadSlotPlayer_fieldTable[] = {
    "_connectNO",
    "_saveDataList",
    "_accessPlList",
};
static igMetaField **g_beNDMWLoadSlotPlayer_fieldHandles[] = {
    &g_beNDMWLoadSlotPlayer_connectNOMetaField,
    &g_beNDMWLoadSlotPlayer_saveDataListMetaField,
    &g_beNDMWLoadSlotPlayer_accessPlListMetaField,
};
static int g_beNDMWLoadSlotPlayer_fieldOffsets[] = {
    8,
    12,
    16,
};

void beNDMWLoadSlotPlayer_InitFields(void) {
    int base;
    void *accessPlList;
    void *saveDataList;
    igMetaObject *meta;

    meta = g_beNDMWLoadSlotPlayer_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWLoadSlotPlayer_ctorTable, 3);
    saveDataList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)saveDataList)->_metaObject = (int)beNDMWDegiDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)saveDataList)->_construct = 1;
    accessPlList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)accessPlList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)accessPlList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWLoadSlotPlayer_fieldTable, g_beNDMWLoadSlotPlayer_fieldHandles, g_beNDMWLoadSlotPlayer_fieldOffsets, base);
}

