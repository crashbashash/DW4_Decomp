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

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igMaterialAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igMaterialAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMaterialAttr_Register);
}

CallbackArray *igMaterialAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMaterialAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igMaterialAttr_GetMetaObjectFunction,
        "igMaterialAttr",
        0x54, /* instance size */
        igMaterialAttr_GetVTable,
        &igMaterialAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMaterialAttr_GetMetaObjectFunction(void) {
    igMaterialAttr_GetMetaObject();
}

static FieldFactory g_igMaterialAttr_ctorTable[] = {
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igVec4fMetaField_CreateInstance,
    (FieldFactory)igUnsignedIntMetaField_Create,
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
    int base;
    igMetaObject *meta;
    int field;
    int field2;
    int field3;
    int field4;
    struct V v1;
    struct V v2;
    struct V v3;
    struct V v4;

    meta = g_igMaterialAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igMaterialAttr_ctorTable, 6);
    field4 = (int)igMetaObject_GetFieldAt(meta, base + 1);
    v1.x = 0;
    v1.w = 0x3F800000;
    v1.y = 0;
    v1.z = 0;
    igVec4fMetaField_SetDefault((igMetaField *)field4, (const float *)&v1);
    field3 = (int)igMetaObject_GetFieldAt(meta, base + 2);
    v2.x = 0;
    v2.w = 0x3F800000;
    v2.y = 0;
    v2.z = 0;
    igVec4fMetaField_SetDefault((igMetaField *)field3, (const float *)&v2);
    field2 = (int)igMetaObject_GetFieldAt(meta, base + 3);
    v3.x = 0;
    v3.w = 0x3F800000;
    v3.y = 0;
    v3.z = 0;
    igVec4fMetaField_SetDefault((igMetaField *)field2, (const float *)&v3);
    field = (int)igMetaObject_GetFieldAt(meta, base + 4);
    v4.x = 0;
    v4.w = 0x3F800000;
    v4.y = 0;
    v4.z = 0;
    igVec4fMetaField_SetDefault((igMetaField *)field, (const float *)&v4);
    igMetaObject_NameFields(meta, g_igMaterialAttr_fieldTable, g_igMaterialAttr_fieldHandles, g_igMaterialAttr_fieldOffsets, base);
}

