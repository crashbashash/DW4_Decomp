igMetaObject *g_beNDMWLoadSavePlWork_metaObject;
igMetaField *g_beNDMWLoadSavePlWork_isEntryMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isRdyMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isCloseMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isCtrlMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isCutConnectMetaField;
igMetaField *g_beNDMWLoadSavePlWork_utilReturnMetaField;
igMetaField *g_beNDMWLoadSavePlWork_utilNextMetaField;
igMetaField *g_beNDMWLoadSavePlWork_isHaveSaveDataMetaField;
igMetaField *g_beNDMWLoadSavePlWork_haveSaveDataMetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysStat0MetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysStat1MetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysStat2MetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysStat3MetaField;
igMetaField *g_beNDMWLoadSavePlWork_sysCount0MetaField;

beNDMWLoadSavePlWork *beNDMWLoadSavePlWork_Create(int allocator) {
    beNDMWLoadSavePlWork_EnsureRegistered();
    return (beNDMWLoadSavePlWork *)igMetaObject_CreateInstance(g_beNDMWLoadSavePlWork_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWLoadSavePlWork_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSavePlWork_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadSavePlWork_EnsureRegistered();
    }
    return g_beNDMWLoadSavePlWork_metaObject;
}

int beNDMWLoadSavePlWork_GetVTable(void) {
    beNDMWLoadSavePlWork obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWLoadSavePlWork_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNDMWLoadSavePlWork_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSavePlWork_Register);
}

static igMetaObjectCallback g_beNDMWLoadSavePlWork_callbackList[] = { beNDMWLoadSlotPlayer_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadSavePlWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadSavePlWork_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWLoadSavePlWork_GetMetaObject,
        "beNDMWLoadSavePlWork",
        0x34, /* instance size */
        beNDMWLoadSavePlWork_GetVTable,
        beNDMWLoadSavePlWork_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadSavePlWork_callbackList /* callback list */
    );
}

void beNDMWLoadSavePlWork_GetMetaObject(void)
{
    beNDMWLoadSavePlWork_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadSavePlWork_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadSavePlWork_fieldTable[] = {
    "_isEntry",
    "_isRdy",
    "_isClose",
    "_isCtrl",
    "_isCutConnect",
    "_utilReturn",
    "_utilNext",
    "_isHaveSaveData",
    "_haveSaveData",
    "_sysStat0",
    "_sysStat1",
    "_sysStat2",
    "_sysStat3",
    "_sysCount0",
};
static igMetaField **g_beNDMWLoadSavePlWork_fieldHandles[] = {
    &g_beNDMWLoadSavePlWork_isEntryMetaField,
    &g_beNDMWLoadSavePlWork_isRdyMetaField,
    &g_beNDMWLoadSavePlWork_isCloseMetaField,
    &g_beNDMWLoadSavePlWork_isCtrlMetaField,
    &g_beNDMWLoadSavePlWork_isCutConnectMetaField,
    &g_beNDMWLoadSavePlWork_utilReturnMetaField,
    &g_beNDMWLoadSavePlWork_utilNextMetaField,
    &g_beNDMWLoadSavePlWork_isHaveSaveDataMetaField,
    &g_beNDMWLoadSavePlWork_haveSaveDataMetaField,
    &g_beNDMWLoadSavePlWork_sysStat0MetaField,
    &g_beNDMWLoadSavePlWork_sysStat1MetaField,
    &g_beNDMWLoadSavePlWork_sysStat2MetaField,
    &g_beNDMWLoadSavePlWork_sysStat3MetaField,
    &g_beNDMWLoadSavePlWork_sysCount0MetaField,
};
static int g_beNDMWLoadSavePlWork_fieldOffsets[] = {
    12,
    13,
    14,
    15,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    8,
};

void beNDMWLoadSavePlWork_InitFields(void) {
    int base;
    void *haveSaveData;
    igMetaObject *meta;

    meta = g_beNDMWLoadSavePlWork_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWLoadSavePlWork_ctorTable, 0xE);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 3), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 4), 1);
    haveSaveData = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)haveSaveData)->_metaObject = (int)beNDMWLoadSlotPlayer_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)haveSaveData)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beNDMWLoadSavePlWork_fieldTable, g_beNDMWLoadSavePlWork_fieldHandles, g_beNDMWLoadSavePlWork_fieldOffsets, base);
}

