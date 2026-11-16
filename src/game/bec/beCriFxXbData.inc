igMetaObject *g_beCriFxXbData_metaObject;
igMetaField *g_beCriFxXbData_lRoomMetaField;
igMetaField *g_beCriFxXbData_lRoomHFMetaField;
igMetaField *g_beCriFxXbData_flRoomRolloffFactorMetaField;
igMetaField *g_beCriFxXbData_flDecayTimeMetaField;
igMetaField *g_beCriFxXbData_flDecayHFRatioMetaField;
igMetaField *g_beCriFxXbData_lReflectionsMetaField;
igMetaField *g_beCriFxXbData_flReflectionsDelayMetaField;
igMetaField *g_beCriFxXbData_lReverbMetaField;
igMetaField *g_beCriFxXbData_flReverbDelayMetaField;
igMetaField *g_beCriFxXbData_flDiffusionMetaField;
igMetaField *g_beCriFxXbData_flDensityMetaField;
igMetaField *g_beCriFxXbData_flHFReferenceMetaField;

igMetaObject *beCriFxXbData_GetOrCreateMetaObject(void) {
    if (g_beCriFxXbData_metaObject == 0) {
        g_beCriFxXbData_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beCriFxXbData_metaObject;
}

void *beCriFxXbData_GetMetaObject(void) {
    igMetaObject *g = g_beCriFxXbData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCriFxXbData_EnsureRegistered();
    }
    return g_beCriFxXbData_metaObject;
}

int beCriFxXbData_GetVTable(void) {
    union U_367040 u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_beCriFxXbData_vtable[0]);
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void beCriFxXbData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCriFxXbData_Register);
}

void *beCriFxXbData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriFxXbData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriFxXbData_GetMetaObjectFunction,
        "beCriFxXbData",
        0x38, /* instance size */
        beCriFxXbData_GetVTable,
        beCriFxXbData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriFxXbData_GetMetaObjectFunction(void)
{
    beCriFxXbData_GetMetaObject();
}

static FieldFactory g_beCriFxXbData_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beCriFxXbData_fieldTable[] = {
    "_lRoom",
    "_lRoomHF",
    "_flRoomRolloffFactor",
    "_flDecayTime",
    "_flDecayHFRatio",
    "_lReflections",
    "_flReflectionsDelay",
    "_lReverb",
    "_flReverbDelay",
    "_flDiffusion",
    "_flDensity",
    "_flHFReference",
};
static igMetaField **g_beCriFxXbData_fieldHandles[] = {
    &g_beCriFxXbData_lRoomMetaField,
    &g_beCriFxXbData_lRoomHFMetaField,
    &g_beCriFxXbData_flRoomRolloffFactorMetaField,
    &g_beCriFxXbData_flDecayTimeMetaField,
    &g_beCriFxXbData_flDecayHFRatioMetaField,
    &g_beCriFxXbData_lReflectionsMetaField,
    &g_beCriFxXbData_flReflectionsDelayMetaField,
    &g_beCriFxXbData_lReverbMetaField,
    &g_beCriFxXbData_flReverbDelayMetaField,
    &g_beCriFxXbData_flDiffusionMetaField,
    &g_beCriFxXbData_flDensityMetaField,
    &g_beCriFxXbData_flHFReferenceMetaField,
};
static int g_beCriFxXbData_fieldOffsets[] = {
    8,
    12,
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
};

void beCriFxXbData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriFxXbData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beCriFxXbData_ctorTable, 0xC);
    igMetaObject_NameFields(temp_s0, g_beCriFxXbData_fieldTable, g_beCriFxXbData_fieldHandles, g_beCriFxXbData_fieldOffsets, temp_s1);
}

