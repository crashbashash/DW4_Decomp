igMetaObject *g_beNDMWLoadSlotPlayer_metaObject;
igMetaField *g_beNDMWLoadSlotPlayer_connectNOMetaField;
igMetaField *g_beNDMWLoadSlotPlayer_saveDataListMetaField;
igMetaField *g_beNDMWLoadSlotPlayer_accessPlListMetaField;

void beNDMWLoadSlotPlayer_Create(int allocator) {
    beNDMWLoadSlotPlayer_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadSlotPlayer_metaObject, allocator);
}

igMetaObject *beNDMWLoadSlotPlayer_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadSlotPlayer_metaObject == 0) {
        g_beNDMWLoadSlotPlayer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    Obj_3c6440 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNDMWLoadSlotPlayer_vtable[0];
    obj.m12 = 0;
    obj.m16 = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWLoadSlotPlayer_vtable[0];
    obj.rel16();
    obj.rel12();
    return r;
}

void beNDMWLoadSlotPlayer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSlotPlayer_Register);
}

static igMetaObjectCallback g_beNDMWLoadSlotPlayer_callbackList[] = { beNDMWDegiDataList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWLoadSlotPlayer_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadSlotPlayer_metaObject,
        igObject_Register,
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
    ((igObjectRefMetaField *)accessPlList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)accessPlList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWLoadSlotPlayer_fieldTable, g_beNDMWLoadSlotPlayer_fieldHandles, g_beNDMWLoadSlotPlayer_fieldOffsets, base);
}

