void FUN_001a4830(int arg0) {
    FUN_001a4970();
    igMetaObject_CreateInstance((int)g_igBoundingBoxesMaker_metaObject, arg0);
}

igMetaObject *g_igBoundingBoxesMaker_metaObject;
igMetaField *g_igBoundingBoxesMaker_timeMetaField;
igMetaField *g_igBoundingBoxesMaker_useWholeAnimationMetaField;
igMetaField *g_igBoundingBoxesMaker_setBoundingBoxesMetaField;
igMetaField *g_igBoundingBoxesMaker_skinnedBoxMetaField;
igMetaField *g_igBoundingBoxesMaker_bboxListMetaField;
igMetaField *g_igBoundingBoxesMaker_preserveActorBoxesMetaField;
igMetaField *g_igBoundingBoxesMaker_exclusionListMetaField;
igMetaField *g_igBoundingBoxesMaker_metaObjectListMetaField;

igMetaObject *igBoundingBoxesMaker_GetMetaObject(void)
{
    igMetaObject *g = g_igBoundingBoxesMaker_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a4970();
    return g_igBoundingBoxesMaker_metaObject;
}

int igBoundingBoxesMaker_GetVTable(void) {
    struct Obj_1a48c0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_igBoundingBoxesMaker_vtable[0];
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_igBoundingBoxesMaker_vtable[0];
    igSmartPointer_igMetaObjectList_Destruct(&obj.w[8], -1);
    igSmartPointer_igStringObj_Destruct(&obj.w[7], -1);
    FUN_0014dd40(&obj.w[5], -1);
    FUN_00198190((void * *)&obj.w[4], -1);
    return r;
}

void FUN_001a4970(void)
{
    igMetaObject_RunStaticInit(igBoundingBoxesMaker_Register);
}

static igMetaObjectCallback g_igBoundingBoxesMaker_callbackList[] = { igAABox_EnsureRegistered, igObjectStringMap_EnsureRegistered, igStringObj_EnsureRegistered, igMetaObjectList_EnsureRegistered, 0 };

void igBoundingBoxesMaker_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoundingBoxesMaker_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igBoundingBoxesMaker_GetMetaObject,
        "igBoundingBoxesMaker",
        0x28, /* instance size */
        igBoundingBoxesMaker_GetVTable,
        &igBoundingBoxesMaker_InitFields,
        0, /* extra callback item */
        g_igBoundingBoxesMaker_callbackList /* callback list */
    );
}

void thunk_igBoundingBoxesMaker_GetMetaObject(void) {
    igBoundingBoxesMaker_GetMetaObject();
}

static FieldFactory g_igBoundingBoxesMaker_ctorTable[] = {
    igLongMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igBoundingBoxesMaker_fieldTable[] = {
    "_time",
    "_useWholeAnimation",
    "_setBoundingBoxes",
    "_skinnedBox",
    "_bboxList",
    "_preserveActorBoxes",
    "_exclusionList",
    "_metaObjectList",
};
static igMetaField **g_igBoundingBoxesMaker_fieldHandles[] = {
    &g_igBoundingBoxesMaker_timeMetaField,
    &g_igBoundingBoxesMaker_useWholeAnimationMetaField,
    &g_igBoundingBoxesMaker_setBoundingBoxesMetaField,
    &g_igBoundingBoxesMaker_skinnedBoxMetaField,
    &g_igBoundingBoxesMaker_bboxListMetaField,
    &g_igBoundingBoxesMaker_preserveActorBoxesMetaField,
    &g_igBoundingBoxesMaker_exclusionListMetaField,
    &g_igBoundingBoxesMaker_metaObjectListMetaField,
};
static int g_igBoundingBoxesMaker_fieldOffsets[] = {
    8,
    16,
    17,
    20,
    24,
    28,
    32,
    36,
};

void igBoundingBoxesMaker_InitFields(void) {
    int temp_s2;
    void *temp_s1_4;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBoundingBoxesMaker_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igBoundingBoxesMaker_ctorTable, 8);
    igLongMetaField_SetDefault(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)), -1);
    igBoolMetaField_SetDefaultValue(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1)), 1);
    igBoolMetaField_SetDefaultValue(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2)), 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igAABox_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 4)));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igObjectStringMap_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5)), 1);
    temp_s1_3 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6)));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igStringObj_GetOrCreateMetaObject();
    temp_s1_4 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2 + 7)));
    ((igObjectRefMetaField *)temp_s1_4)->_metaObject = igMetaObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igBoundingBoxesMaker_fieldTable, g_igBoundingBoxesMaker_fieldHandles, g_igBoundingBoxesMaker_fieldOffsets, temp_s2);
}

