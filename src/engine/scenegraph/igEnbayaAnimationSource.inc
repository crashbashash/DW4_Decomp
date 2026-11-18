static const char *g_igEnbayaAnimationSource_playModeNames[] = {
    "REPEAT", "CLAMP", "BOUNCE", "LOOP",
    "OFFSET_CLAMP",
};
static int g_igEnbayaAnimationSource_playModeValues[] = {
    0, 1, 2, 3, 4,
};
igMetaEnum *g_igEnbayaAnimationSource_playModeMetaEnum;

igMetaEnum *FUN_001a21b0(void) {
    if (g_igEnbayaAnimationSource_playModeMetaEnum == 0) {
        g_igEnbayaAnimationSource_playModeMetaEnum = igMetaEnum_Create("PLAY_MODE", g_igEnbayaAnimationSource_playModeNames, g_igEnbayaAnimationSource_playModeValues, 5);
    }
    return g_igEnbayaAnimationSource_playModeMetaEnum;
}

igMetaObject *g_igEnbayaAnimationSource_metaObject;
igMetaField *g_igEnbayaAnimationSource_enbayaAnimationStreamMetaField;
igMetaField *g_igEnbayaAnimationSource_interpolationMethodMetaField;
igMetaField *g_igEnbayaAnimationSource_drivenChannelsMetaField;
igMetaField *g_igEnbayaAnimationSource_playModeMetaField;
igMetaField *g_igEnbayaAnimationSource_lastUpdateTimefMetaField;
igMetaField *g_igEnbayaAnimationSource_lastUpdateTimeMetaField;

igMetaObject *FUN_001a2210(void) {
    if (g_igEnbayaAnimationSource_metaObject == 0) {
        g_igEnbayaAnimationSource_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igEnbayaAnimationSource_metaObject;
}

igMetaObject *igEnbayaAnimationSource_GetMetaObject(void)
{
    igMetaObject *g = g_igEnbayaAnimationSource_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnbayaAnimationSource_EnsureRegistered();
    return g_igEnbayaAnimationSource_metaObject;
}

int igEnbayaAnimationSource_GetVTable(void) {
    union U_1a22b0 u;

    igObject_InitHeader((igObject *)u.b);
    u.w[0] = (int)(&g_igEnbayaAnimationSource_vtable[0]);
    return *(int *)&u.b[g_objectSystem->vtableProbeOffset];
}

void igEnbayaAnimationSource_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEnbayaAnimationSource_Register);
}

CallbackArray *igEnbayaAnimationSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEnbayaAnimationSource_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEnbayaAnimationSource_GetMetaObject,
        "igEnbayaAnimationSource",
        sizeof(igEnbayaAnimationSource),               /* Instance size. */
        igEnbayaAnimationSource_GetVTable,
        &igEnbayaAnimationSource_InitFields,
        FUN_001a24d0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEnbayaAnimationSource_GetMetaObject(void) {
    igEnbayaAnimationSource_GetMetaObject();
}

static FieldFactory g_igEnbayaAnimationSource_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igUnsignedCharArrayMetaField_Create,
    (FieldFactory)igUnsignedCharMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
};
static const char *g_igEnbayaAnimationSource_fieldTable[] = {
    "_enbayaAnimationStream",
    "_interpolationMethod",
    "_drivenChannels",
    "_playMode",
    "_lastUpdateTimef",
    "_lastUpdateTime",
};
static igMetaField **g_igEnbayaAnimationSource_fieldHandles[] = {
    &g_igEnbayaAnimationSource_enbayaAnimationStreamMetaField,
    &g_igEnbayaAnimationSource_interpolationMethodMetaField,
    &g_igEnbayaAnimationSource_drivenChannelsMetaField,
    &g_igEnbayaAnimationSource_playModeMetaField,
    &g_igEnbayaAnimationSource_lastUpdateTimefMetaField,
    &g_igEnbayaAnimationSource_lastUpdateTimeMetaField,
};
static int g_igEnbayaAnimationSource_fieldOffsets[] = {
    32,
    8,
    11,
    12,
    16,
    24,
};

void igEnbayaAnimationSource_InitFields(void) {
    igMemoryRefMetaField *temp_s2;
    igFloatMetaField *temp_v0;
    igLongMetaField *temp_v0_2;
    igUnsignedCharArrayMetaField *tf;
    igEnumMetaField *tf2;
    void *temp_s1;
    int temp_s0;
    temp_s1 = (void *)g_igEnbayaAnimationSource_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igEnbayaAnimationSource_ctorTable, 6);
    temp_s2 = (igMemoryRefMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0);
    temp_s2->_memType = igCharMetaField_GetDefaultDescriptor();
    temp_s2->_destruct = 1;
    temp_s2->_releaseOnCopy = 1;
    temp_s2->_releaseOnReset = 1;
    tf = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1);
    tf->_num = 3;
    igUnsignedCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2), 3);
    tf2 = (igEnumMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3);
    tf2->_getMetaEnumFunction = (int)FUN_001a21b0;
    temp_v0 = (igFloatMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4);
    igFloatMetaField_SetDefault((igMetaField *)temp_v0, -1.0f);
    temp_v0->_persistent = 0;
    temp_v0_2 = (igLongMetaField *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5);
    igLongMetaField_SetDefault((igMetaField *)temp_v0_2, -1);
    temp_v0_2->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igEnbayaAnimationSource_fieldTable, g_igEnbayaAnimationSource_fieldHandles, g_igEnbayaAnimationSource_fieldOffsets, temp_s0);
    igMetaObject_AddExitCallback((int)FUN_001a24e0);
}

void FUN_001a24d0(void) {
    FUN_001c07d0();
}

void FUN_001a24e0(void) {
    FUN_001c07e0();
}

