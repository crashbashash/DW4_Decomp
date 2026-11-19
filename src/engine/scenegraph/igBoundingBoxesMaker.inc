igBoundingBoxesMaker *igBoundingBoxesMaker_Create(igMemoryPoolView *pool) {
    igBoundingBoxesMaker_EnsureRegistered();
    return (igBoundingBoxesMaker *)igMetaObject_CreateInstance(g_igBoundingBoxesMaker_metaObject, pool);
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
        igBoundingBoxesMaker_EnsureRegistered();
    return g_igBoundingBoxesMaker_metaObject;
}

int igBoundingBoxesMaker_GetVTable(void) {
    struct Obj_1a48c0 obj;
    int r;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igBoundingBoxesMaker_vtable[0];
    obj.w[4] = 0;
    obj.w[5] = 0;
    obj.w[7] = 0;
    obj.w[8] = 0;
    r = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj.vt = &g_igBoundingBoxesMaker_vtable[0];
    igSmartPointer_igMetaObjectList_Destruct((igSmartPointer<igObject> *)&obj.w[8], -1);
    igSmartPointer_igStringObj_Destruct((igSmartPointer<igObject> *)&obj.w[7], -1);
    FUN_0014dd40((igSmartPointer<igObject> *)&obj.w[5], -1);
    igSmartPointer_igAABox_Destruct((igSmartPointer<igObject> *)&obj.w[4], -1);
    return r;
}

void igBoundingBoxesMaker_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBoundingBoxesMaker_Register);
}

static igMetaObjectCallback g_igBoundingBoxesMaker_callbackList[] = { igAABox_EnsureRegistered, igObjectStringMap_EnsureRegistered, igStringObj_EnsureRegistered, igMetaObjectList_EnsureRegistered, 0 };

CallbackArray *igBoundingBoxesMaker_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoundingBoxesMaker_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igBoundingBoxesMaker_GetMetaObjectFunction,
        "igBoundingBoxesMaker",
        0x28, /* instance size */
        igBoundingBoxesMaker_GetVTable,
        &igBoundingBoxesMaker_InitFields,
        0, /* extra callback item */
        g_igBoundingBoxesMaker_callbackList /* callback list */
    );
}

void igBoundingBoxesMaker_GetMetaObjectFunction(void) {
    igBoundingBoxesMaker_GetMetaObject();
}

static FieldFactory g_igBoundingBoxesMaker_ctorTable[] = {
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
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
    int base;
    void *metaObjectListField;
    void *exclusionListField;
    void *bboxListField;
    void *skinnedBoxField;
    void *meta;

    meta = (void *)g_igBoundingBoxesMaker_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igBoundingBoxesMaker_ctorTable, 8);
    igLongMetaField_SetDefault(igMetaObject_GetFieldAt((igMetaObject *)meta, base), -1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2), 1);
    skinnedBoxField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)skinnedBoxField)->_metaObject = (int)igAABox_GetOrCreateMetaObject();
    ((igRefMetaField *)skinnedBoxField)->_construct = 1;
    bboxListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((igObjectRefMetaField *)bboxListField)->_metaObject = (int)igObjectStringMap_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5), 1);
    exclusionListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)exclusionListField)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    metaObjectListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7)));
    ((igObjectRefMetaField *)metaObjectListField)->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igBoundingBoxesMaker_fieldTable, g_igBoundingBoxesMaker_fieldHandles, g_igBoundingBoxesMaker_fieldOffsets, base);
}

