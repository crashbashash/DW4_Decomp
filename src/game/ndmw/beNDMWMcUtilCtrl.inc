igMetaObject *g_beNDMWMcUtilCtrl_metaObject;
igMetaField *g_beNDMWMcUtilCtrl_messengerMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isUseUtilMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isRdyMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isRunMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isMtapMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isFormatRunMetaField;
igMetaField *g_beNDMWMcUtilCtrl_tgConMetaField;
igMetaField *g_beNDMWMcUtilCtrl_usePlNoMetaField;
igMetaField *g_beNDMWMcUtilCtrl_kindMetaField;
igMetaField *g_beNDMWMcUtilCtrl_resultMetaField;
igMetaField *g_beNDMWMcUtilCtrl_isResultMetaField;
igMetaField *g_beNDMWMcUtilCtrl_svDataMetaField;
igMetaField *g_beNDMWMcUtilCtrl_slotMetaField;
igMetaField *g_beNDMWMcUtilCtrl_st0MetaField;
igMetaField *g_beNDMWMcUtilCtrl_st1MetaField;
igMetaField *g_beNDMWMcUtilCtrl_st2MetaField;
igMetaField *g_beNDMWMcUtilCtrl_st3MetaField;

beNDMWMcUtilCtrl *beNDMWMcUtilCtrl_Create(int allocator) {
    beNDMWMcUtilCtrl_EnsureRegistered();
    return (beNDMWMcUtilCtrl *)igMetaObject_CreateInstance(g_beNDMWMcUtilCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWMcUtilCtrl_GetOrCreateMetaObject(void) {
    if (g_beNDMWMcUtilCtrl_metaObject == 0) {
        g_beNDMWMcUtilCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWMcUtilCtrl_metaObject;
}

void *beNDMWMcUtilCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMcUtilCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMcUtilCtrl_EnsureRegistered();
    }
    return g_beNDMWMcUtilCtrl_metaObject;
}

int beNDMWMcUtilCtrl_GetVTable(void) {
    beNDMWMcUtilCtrl obj;
    igObject *o;
    int t;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWMcUtilCtrl_vtable[0];
    obj._svData = 0;
    obj._slot = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWMcUtilCtrl_vtable[0];
    if (&obj._slot != 0) {
        o = (igObject *)obj._slot;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    if (&obj._svData != 0) {
        o = (igObject *)obj._svData;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    return t;
}

void beNDMWMcUtilCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMcUtilCtrl_Register);
}

static igMetaObjectCallback g_beNDMWMcUtilCtrl_callbackList[] = { beMessenger_EnsureRegistered, beSaveDataDeliver_EnsureRegistered, beNDMWMcSlotList_EnsureRegistered, 0 };

CallbackArray *beNDMWMcUtilCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMcUtilCtrl_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWMcUtilCtrl_GetMetaObject,
        "beNDMWMcUtilCtrl",
        0x40, /* instance size */
        beNDMWMcUtilCtrl_GetVTable,
        beNDMWMcUtilCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWMcUtilCtrl_callbackList /* callback list */
    );
}

void beNDMWMcUtilCtrl_GetMetaObject(void)
{
    beNDMWMcUtilCtrl_ResolveMetaObject();
}

static FieldFactory g_beNDMWMcUtilCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWMcUtilCtrl_fieldTable[] = {
    "_messenger",
    "_isUseUtil",
    "_isRdy",
    "_isRun",
    "_isMtap",
    "_isFormatRun",
    "_tgCon",
    "_usePlNo",
    "_kind",
    "_result",
    "_isResult",
    "_svData",
    "_slot",
    "_st0",
    "_st1",
    "_st2",
    "_st3",
};
static igMetaField **g_beNDMWMcUtilCtrl_fieldHandles[] = {
    &g_beNDMWMcUtilCtrl_messengerMetaField,
    &g_beNDMWMcUtilCtrl_isUseUtilMetaField,
    &g_beNDMWMcUtilCtrl_isRdyMetaField,
    &g_beNDMWMcUtilCtrl_isRunMetaField,
    &g_beNDMWMcUtilCtrl_isMtapMetaField,
    &g_beNDMWMcUtilCtrl_isFormatRunMetaField,
    &g_beNDMWMcUtilCtrl_tgConMetaField,
    &g_beNDMWMcUtilCtrl_usePlNoMetaField,
    &g_beNDMWMcUtilCtrl_kindMetaField,
    &g_beNDMWMcUtilCtrl_resultMetaField,
    &g_beNDMWMcUtilCtrl_isResultMetaField,
    &g_beNDMWMcUtilCtrl_svDataMetaField,
    &g_beNDMWMcUtilCtrl_slotMetaField,
    &g_beNDMWMcUtilCtrl_st0MetaField,
    &g_beNDMWMcUtilCtrl_st1MetaField,
    &g_beNDMWMcUtilCtrl_st2MetaField,
    &g_beNDMWMcUtilCtrl_st3MetaField,
};
static int g_beNDMWMcUtilCtrl_fieldOffsets[] = {
    8,
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
    52,
    56,
    60,
};

void beNDMWMcUtilCtrl_InitFields(void) {
    int base;
    void *slot;
    void *svData;
    void *messenger;
    igMetaObject *meta;

    meta = g_beNDMWMcUtilCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWMcUtilCtrl_ctorTable, 0x11);
    messenger = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)messenger)->_metaObject = (int)beMessenger_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)messenger)->_refCounted = 0;
    svData = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)svData)->_metaObject = (int)beSaveDataDeliver_GetOrCreateMetaObject();
    ((igRefMetaField *)svData)->_construct = 1;
    slot = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)slot)->_metaObject = (int)beNDMWMcSlotList_GetOrCreateMetaObject();
    ((igRefMetaField *)slot)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWMcUtilCtrl_fieldTable, g_beNDMWMcUtilCtrl_fieldHandles, g_beNDMWMcUtilCtrl_fieldOffsets, base);
}

