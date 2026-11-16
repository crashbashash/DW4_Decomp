igMetaObject *g_igMaterialAttr_metaObject;
igMetaField *g_igMaterialAttr_shininessMetaField;
igMetaField *g_igMaterialAttr_diffuseMetaField;
igMetaField *g_igMaterialAttr_ambientMetaField;
igMetaField *g_igMaterialAttr_emissionMetaField;
igMetaField *g_igMaterialAttr_specularMetaField;
igMetaField *g_igMaterialAttr_flagsMetaField;

igMetaObject *igMaterialAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMaterialAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMaterialAttr_EnsureRegistered();
    return g_igMaterialAttr_metaObject;
}

int igMaterialAttr_GetVTable(void) {
    struct Obj_135c30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igMaterialAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igMaterialAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMaterialAttr_Register);
}

void igMaterialAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMaterialAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igMaterialAttr_GetMetaObject,
        "igMaterialAttr",
        0x54, /* instance size */
        igMaterialAttr_GetVTable,
        &igMaterialAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMaterialAttr_GetMetaObject(void) {
    igMaterialAttr_GetMetaObject();
}

static FieldFactory g_igMaterialAttr_ctorTable[] = {
    igFloatMetaField_Create,
    FUN_001872a0,
    FUN_001872a0,
    FUN_001872a0,
    FUN_001872a0,
    igUnsignedIntMetaField_Create,
};
static const char *g_igMaterialAttr_fieldTable[] = {
    "_shininess",
    "_diffuse",
    "_ambient",
    "_emission",
    "_specular",
    "_flags",
};
static igMetaField **g_igMaterialAttr_fieldHandles[] = {
    &g_igMaterialAttr_shininessMetaField,
    &g_igMaterialAttr_diffuseMetaField,
    &g_igMaterialAttr_ambientMetaField,
    &g_igMaterialAttr_emissionMetaField,
    &g_igMaterialAttr_specularMetaField,
    &g_igMaterialAttr_flagsMetaField,
};
static int g_igMaterialAttr_fieldOffsets[] = {
    12,
    16,
    32,
    48,
    64,
    80,
};

void igMaterialAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;
    int temp_a0_4;
    int temp_a0_3;
    int temp_a0_2;
    int temp_a0;
    struct V v1;
    struct V v2;
    struct V v3;
    struct V v4;

    temp_s0 = g_igMaterialAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igMaterialAttr_ctorTable, 6);
    temp_a0 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    v1.x = 0;
    v1.w = 0x3F800000;
    v1.y = 0;
    v1.z = 0;
    FUN_0018e670(temp_a0, &v1);
    temp_a0_2 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    v2.x = 0;
    v2.w = 0x3F800000;
    v2.y = 0;
    v2.z = 0;
    FUN_0018e670(temp_a0_2, &v2);
    temp_a0_3 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3);
    v3.x = 0;
    v3.w = 0x3F800000;
    v3.y = 0;
    v3.z = 0;
    FUN_0018e670(temp_a0_3, &v3);
    temp_a0_4 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4);
    v4.x = 0;
    v4.w = 0x3F800000;
    v4.y = 0;
    v4.z = 0;
    FUN_0018e670(temp_a0_4, &v4);
    igMetaObject_NameFields(temp_s0, g_igMaterialAttr_fieldTable, g_igMaterialAttr_fieldHandles, g_igMaterialAttr_fieldOffsets, temp_s1);
}

