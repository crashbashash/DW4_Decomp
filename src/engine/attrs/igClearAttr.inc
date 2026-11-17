igMetaObject *g_igClearAttr_metaObject;
igMetaField *g_igClearAttr_clearModeMetaField;
igMetaField *g_igClearAttr_colorMetaField;
igMetaField *g_igClearAttr_accumMetaField;
igMetaField *g_igClearAttr_depthMetaField;
igMetaField *g_igClearAttr_stencilMetaField;
igMetaField *g_igClearAttr_colorPackedMetaField;
igMetaField *g_igClearAttr_depthFMetaField;

void FUN_00139370(int arg0) {
    igClearAttr_EnsureRegistered();
    igMetaObject_CreateInstance(*(igMetaObject * *)0x55F308, (igMemoryPoolView *)arg0);
}

igMetaObject *igClearAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClearAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igClearAttr_EnsureRegistered();
    return g_igClearAttr_metaObject;
}

int igClearAttr_GetVTable(void) {
    struct Obj_139400 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igClearAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igClearAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igClearAttr_Register);
}

CallbackArray *igClearAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igClearAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igClearAttr_GetMetaObject,
        "igClearAttr",
        0x48, /* instance size */
        igClearAttr_GetVTable,
        &igClearAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igClearAttr_GetMetaObject(void) {
    igClearAttr_GetMetaObject();
}

static FieldFactory g_igClearAttr_ctorTable[] = {
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igDoubleMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
};
static const char *g_igClearAttr_fieldTable[] = {
    "_clearMode",
    "_color",
    "_accum",
    "_depth",
    "_stencil",
    "_colorPacked",
    "_depthF",
};
static igMetaField **g_igClearAttr_fieldHandles[] = {
    &g_igClearAttr_clearModeMetaField,
    &g_igClearAttr_colorMetaField,
    &g_igClearAttr_accumMetaField,
    &g_igClearAttr_depthMetaField,
    &g_igClearAttr_stencilMetaField,
    &g_igClearAttr_colorPackedMetaField,
    &g_igClearAttr_depthFMetaField,
};
static int g_igClearAttr_fieldOffsets[] = {
    12,
    16,
    32,
    48,
    56,
    60,
    64,
};

void igClearAttr_InitFields(void) {
    void *temp_v0_2;
    void *temp_v0;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s1;
    int temp_s0;
    struct V v1;
    struct V v2;

    temp_s1 = (void *)g_igClearAttr_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igClearAttr_ctorTable, 7);
    temp_a0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1));
    v1.x = 0;
    v1.w = 0x3F800000;
    v1.y = 0;
    v1.z = 0;
    igVec4fMetaField_SetDefault((igMetaField *)temp_a0, (const float *)&v1);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2));
    v2.x = 0;
    v2.y = 0;
    v2.z = 0;
    v2.w = 0;
    igVec4fMetaField_SetDefault((igMetaField *)temp_a0_2, (const float *)&v2);
    igDoubleMetaField_SetDefaultDouble(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3), 1.0);
    temp_v0 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5));
    igUnsignedIntMetaField_SetDefaultValue((igMetaField *)temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6));
    igFloatMetaField_SetDefault((igMetaField *)temp_v0_2, 1.0f);
    *(char *)((char *)(temp_v0_2) + 38) = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igClearAttr_fieldTable, g_igClearAttr_fieldHandles, g_igClearAttr_fieldOffsets, temp_s0);
}

