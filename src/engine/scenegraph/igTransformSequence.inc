igMetaObject *g_igTransformSequence_metaObject;
igMetaField *g_igTransformSequence_xlateListMetaField;
igMetaField *g_igTransformSequence_quatListMetaField;
igMetaField *g_igTransformSequence_scaleListMetaField;
igMetaField *g_igTransformSequence_timeListMetaField;
igMetaField *g_igTransformSequence_startTimeMetaField;
igMetaField *g_igTransformSequence_uniformTimeEnabledMetaField;
igMetaField *g_igTransformSequence_playModeMetaField;
igMetaField *g_igTransformSequence_lastTimeMetaField;
igMetaField *g_igTransformSequence_centerOfRotationMetaField;

igMetaObject *FUN_00195330(void) {
    return g_igTransformSequence_metaObject;
}

static FieldFactory g_igTransformSequence1_5_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedCharMetaField_Create,
    (FieldFactory)igUnsignedCharArrayMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igTransformSequence1_5_fieldTable[] = {
    "_timeListLong",
    "_interpolationDataTranslation",
    "_interpolationDataRotation",
    "_interpolationDataScale",
    "_drivenChannels",
    "_interpolationMethod",
    "_keyframeTimeOffset",
    "_animationDuration",
    "_compressedDataObject",
};
static igMetaField **g_igTransformSequence1_5_fieldHandles[] = {
    &g_igTransformSequence1_5_timeListLongMetaField,
    &g_igTransformSequence1_5_interpolationDataTranslationMetaField,
    &g_igTransformSequence1_5_interpolationDataRotationMetaField,
    &g_igTransformSequence1_5_interpolationDataScaleMetaField,
    &g_igTransformSequence1_5_drivenChannelsMetaField,
    &g_igTransformSequence1_5_interpolationMethodMetaField,
    &g_igTransformSequence1_5_keyframeTimeOffsetMetaField,
    &g_igTransformSequence1_5_animationDurationMetaField,
    &g_igTransformSequence1_5_compressedDataObjectMetaField,
};
static int g_igTransformSequence1_5_fieldOffsets[] = {
    56,
    60,
    64,
    68,
    72,
    73,
    80,
    88,
    96,
};

void igTransformSequence1_5_InitFields(void) {
    int temp_s2;
    int temp_s3;
    igUnsignedCharArrayMetaField *t5;
    void **temp_v0;
    igObjectRefMetaField *temp_s0;
    igObjectRefMetaField *temp_s0_2;
    igObjectRefMetaField *temp_s0_3;
    igObjectRefMetaField *temp_s0_4;
    igObjectRefMetaField *temp_s0_5;
    igMetaObject *temp_s1;
    igMetaField *temp_v0_2;

    temp_s1 = (igMetaObject *)(g_igTransformSequence1_5_metaObject);
    temp_s2 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igTransformSequence1_5_ctorTable, 9);
    temp_s0 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2));
    temp_s0->_metaObject = (int)igLongList_GetOrCreateMetaObject();
    temp_s0->_construct = 1;
    temp_v0 = (void **)(igMetaObject_FindFieldByName(temp_s1, "_timeList"));
    temp_s3 = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)temp_s1->_metaFields, (int)temp_v0);
    temp_v0_2 = (igMetaField *)(((DW4VC_84_1 *)(temp_v0))->vX((int)(1)));
    ((Gap::Core::igObjectRefMetaField *)temp_v0_2)->setDefault((Gap::Core::igObject *)0);
    *(char *)((char *)(temp_v0_2) + 52) = 0;
    temp_v0_2->_externalEnumStorage = (int)(&g_igTransformSequence1_5_timeListMetaField);
    igMetaObject_FinalizeAndReplaceField(temp_s1, temp_s3, temp_v0_2);
    temp_v0_2->_refCount = (int)((int) (temp_v0_2->_refCount - 1));
    if ((temp_v0_2->_refCount & 0x7FFFFF) == 0) {
        igObject_Destroy(temp_v0_2);
    }
    temp_s0_2 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 1));
    temp_s0_2->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    temp_s0_3 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 2));
    temp_s0_3->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    temp_s0_4 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 3));
    temp_s0_4->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    ((Gap::Core::igUnsignedCharMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 4)))->setDefault(0xB);
    t5 = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt(temp_s1, temp_s2 + 5);
    t5->_num = 3;
    ((Gap::Core::igLongMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 7)))->setDefault(-1);
    temp_s0_5 = (igObjectRefMetaField *)(igMetaObject_GetFieldAt(temp_s1, temp_s2 + 8));
    temp_s0_5->_metaObject = (int)igCompressedTransformSequence1_5Data_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s1, g_igTransformSequence1_5_fieldTable, g_igTransformSequence1_5_fieldHandles, g_igTransformSequence1_5_fieldOffsets, temp_s2);
}

void thunk_FUN_001ddfd0(void) {
    FUN_001ddfd0();
}

igMetaObject *igTransformSequence_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformSequence_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransformSequence_EnsureRegistered();
    return g_igTransformSequence_metaObject;
}

void igTransformSequence_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransformSequence_Register);
}

static igMetaObjectCallback g_igTransformSequence_callbackList[] = { igVec3fList_EnsureRegistered, igQuaternionfList_EnsureRegistered, igDoubleList_EnsureRegistered, 0 };

CallbackArray *igTransformSequence_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igTransformSequence_metaObject,
        igTransformSource_Register,
        igTransformSource_GetPublishedMetaObject,
        igTransformSequence_GetMetaObjectFunction,
        "igTransformSequence",
        0x38, /* instance size */
        0,
        &igTransformSequence_InitFields,
        0, /* extra callback item */
        g_igTransformSequence_callbackList /* callback list */
    );
}

void igTransformSequence_GetMetaObjectFunction(void) {
    igTransformSequence_GetMetaObject();
}

igMetaObject *igTransformSource_GetPublishedMetaObject(void) {
    return g_igTransformSource_metaObject;
}

static FieldFactory g_igTransformSequence_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igDoubleMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
};
static const char *g_igTransformSequence_fieldTable[] = {
    "_xlateList",
    "_quatList",
    "_scaleList",
    "_timeList",
    "_startTime",
    "_uniformTimeEnabled",
    "_playMode",
    "_lastTime",
    "_centerOfRotation",
};
static igMetaField **g_igTransformSequence_fieldHandles[] = {
    &g_igTransformSequence_xlateListMetaField,
    &g_igTransformSequence_quatListMetaField,
    &g_igTransformSequence_scaleListMetaField,
    &g_igTransformSequence_timeListMetaField,
    &g_igTransformSequence_startTimeMetaField,
    &g_igTransformSequence_uniformTimeEnabledMetaField,
    &g_igTransformSequence_playModeMetaField,
    &g_igTransformSequence_lastTimeMetaField,
    &g_igTransformSequence_centerOfRotationMetaField,
};
static int g_igTransformSequence_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    32,
    36,
    40,
    44,
};

void igTransformSequence_InitFields(void) {
    int temp_s1;
    struct Fld *temp_a0;
    void *temp_s0;
    struct Fld *temp_s2;
    struct Fld *temp_s2_2;
    struct Fld *temp_s2_3;
    struct Fld *temp_s2_4;
    struct Fld *temp_v0;
    struct Fld *temp_v0_2;
    int sp40[3];

    temp_s0 = (void *)(g_igTransformSequence_metaObject);
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igTransformSequence_ctorTable, 9);
    temp_s2 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1));
    temp_s2->f56 = (int)igVec3fList_GetOrCreateMetaObject();
    temp_s2->f52 = 1;
    temp_s2_2 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1));
    temp_s2_2->f56 = (int)igQuaternionfList_GetOrCreateMetaObject();
    temp_s2_2->f52 = 1;
    temp_s2_3 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2));
    temp_s2_3->f56 = (int)igVec3fList_GetOrCreateMetaObject();
    temp_s2_3->f52 = 1;
    temp_s2_4 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3));
    temp_s2_4->f56 = (int)igDoubleList_GetOrCreateMetaObject();
    temp_s2_4->f52 = 1;
    ((Gap::Core::igDoubleMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4)))->setDefault(-1.0);
    temp_v0 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6));
    ((Gap::Core::igEnumMetaField *)temp_v0)->setDefault(0);
    *(int *)((char *)temp_v0 + 52) = (int)&igMetaEnum_GetEmpty;
    temp_v0_2 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7));
    ((Gap::Core::igIntMetaField *)temp_v0_2)->setDefault(1);
    temp_v0_2->f38 = 0;
    temp_a0 = ((struct Fld *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8));
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    ((Gap::Math::igVec3fMetaField *)temp_a0)->setDefault(*(const igVec3f *)sp40);
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igTransformSequence_fieldTable, g_igTransformSequence_fieldHandles, g_igTransformSequence_fieldOffsets, temp_s1);
    *(int *)((char *)(g_igTransformSequence_metaObject) + 60) = (int)(igTransformSequence1_5_GetMetaObjectFunction);
}

