igMetaObject *g_beNDMWDegiData_metaObject;
igMetaField *g_beNDMWDegiData_insightMetaField;
igMetaField *g_beNDMWDegiData_isUseMetaField;
igMetaField *g_beNDMWDegiData_idMetaField;
igMetaField *g_beNDMWDegiData_dmkindMetaField;
igMetaField *g_beNDMWDegiData_dmNameMetaField;
igMetaField *g_beNDMWDegiData_dmNameUniMetaField;
igMetaField *g_beNDMWDegiData_lvMetaField;
igMetaField *g_beNDMWDegiData_hpMetaField;
igMetaField *g_beNDMWDegiData_maxHpMetaField;
igMetaField *g_beNDMWDegiData_mpMetaField;
igMetaField *g_beNDMWDegiData_maxMpMetaField;
igMetaField *g_beNDMWDegiData_dataSizeMetaField;
igMetaField *g_beNDMWDegiData_dataMetaField;

beNDMWDegiData *beNDMWDegiData_Create(int allocator) {
    beNDMWDegiData_RunStaticInit();
    return (beNDMWDegiData *)igMetaObject_CreateInstance(g_beNDMWDegiData_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWDegiData_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWDegiData_metaObject;
    bool ready;
    if (g) {
        /* matching construct: the bool compared against false keeps the retail sltu normalisation under the
         * unit profile (exceptions on); `if (ready = ...)` folds it away */
        ready = g->_validity & 4;
        if (ready != false) goto end;
    }
    beNDMWDegiData_RunStaticInit();
end:
    return g_beNDMWDegiData_metaObject;
}

int beNDMWDegiData_GetVTable(void) {
    beNDMWDegiData obj;
    int vtable;
    int *dmNameRef;
    int *dmkindRef;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWDegiData_vtable[0];
    dmkindRef = &obj._dmkind;
    *dmkindRef = 0;
    dmNameRef = &obj._dmName;
    *dmNameRef = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWDegiData_vtable[0];
    if (dmNameRef != 0) {
        releaseString((const char *)*dmNameRef);
    }
    if (dmkindRef != 0) {
        releaseString((const char *)*dmkindRef);
    }
    return vtable;
}

void beNDMWDegiData_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(beNDMWDegiData_Register);
}

static igMetaObjectCallback g_beNDMWDegiData_callbackList[] = { igInsightCore_EnsureRegistered, 0 };

CallbackArray *beNDMWDegiData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWDegiData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWDegiData_GetMetaObject,
        "beNDMWDegiData",
        0x4c, /* instance size */
        beNDMWDegiData_GetVTable,
        beNDMWDegiData_InitFields,
        0, /* extra callback item */
        g_beNDMWDegiData_callbackList /* callback list */
    );
}

void beNDMWDegiData_GetMetaObject(void)
{
    beNDMWDegiData_GetReadyMetaObject();
}

static FieldFactory g_beNDMWDegiData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igUnsignedShortArrayMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
};
static const char *g_beNDMWDegiData_fieldTable[] = {
    "_insight",
    "_isUse",
    "_id",
    "_dmkind",
    "_dmName",
    "_dmNameUni",
    "_lv",
    "_hp",
    "_maxHp",
    "_mp",
    "_maxMp",
    "_dataSize",
    "_data",
};
static igMetaField **g_beNDMWDegiData_fieldHandles[] = {
    &g_beNDMWDegiData_insightMetaField,
    &g_beNDMWDegiData_isUseMetaField,
    &g_beNDMWDegiData_idMetaField,
    &g_beNDMWDegiData_dmkindMetaField,
    &g_beNDMWDegiData_dmNameMetaField,
    &g_beNDMWDegiData_dmNameUniMetaField,
    &g_beNDMWDegiData_lvMetaField,
    &g_beNDMWDegiData_hpMetaField,
    &g_beNDMWDegiData_maxHpMetaField,
    &g_beNDMWDegiData_mpMetaField,
    &g_beNDMWDegiData_maxMpMetaField,
    &g_beNDMWDegiData_dataSizeMetaField,
    &g_beNDMWDegiData_dataMetaField,
};
static int g_beNDMWDegiData_fieldOffsets[] = {
    32,
    40,
    44,
    48,
    52,
    8,
    56,
    60,
    64,
    68,
    72,
    36,
    28,
};

void beNDMWDegiData_InitFields(void) {
    igMetaObject *meta;
    int base;
    void *insight;
    void *dmNameUni;
    void *data;

    meta = g_beNDMWDegiData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWDegiData_ctorTable, 0xD);
    insight = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)insight)->_metaObject = (int)igInsightCore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)insight)->_refCounted = 0;
    dmNameUni = igMetaObject_GetFieldAt(meta, base + 5);
    ((igUnsignedShortArrayMetaField *)dmNameUni)->_num = 0xA;
    data = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igMemoryRefMetaField *)data)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(meta, g_beNDMWDegiData_fieldTable, g_beNDMWDegiData_fieldHandles, g_beNDMWDegiData_fieldOffsets, base);
}

