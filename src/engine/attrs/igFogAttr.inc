igMetaObject *g_igFogAttr_metaObject;
igMetaField *g_igFogAttr_modeMetaField;
igMetaField *g_igFogAttr_nearValMetaField;
igMetaField *g_igFogAttr_farValMetaField;
igMetaField *g_igFogAttr_densityMetaField;
igMetaField *g_igFogAttr_colorMetaField;

igMetaObject *igFogAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igFogAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFogAttr_EnsureRegistered();
    return g_igFogAttr_metaObject;
}

int igFogAttr_GetVTable(void) {
    struct Obj_137df0 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igFogAttr_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igFogAttr_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFogAttr_Register);
}

CallbackArray *igFogAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFogAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        igFogAttr_GetMetaObjectFunction,
        "igFogAttr",
        0x2C, /* instance size */
        igFogAttr_GetVTable,
        &igFogAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igFogAttr_GetMetaObjectFunction(void) {
    igFogAttr_GetMetaObject();
}

static FieldFactory g_igFogAttr_ctorTable[] = {
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igVec4fMetaField_CreateInstance,
};
static const char *g_igFogAttr_fieldTable[] = {
    "_mode",
    "_nearVal",
    "_farVal",
    "_density",
    "_color",
};
static igMetaField **g_igFogAttr_fieldHandles[] = {
    &g_igFogAttr_modeMetaField,
    &g_igFogAttr_nearValMetaField,
    &g_igFogAttr_farValMetaField,
    &g_igFogAttr_densityMetaField,
    &g_igFogAttr_colorMetaField,
};
static int g_igFogAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
};

int g_igFogAttr_modeDefault = 2;

void igFogAttr_InitFields(void) {
    int base;
    float sp[4];
    void *field;
    void *field2;
    igMetaObject *meta;

    meta = g_igFogAttr_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igFogAttr_ctorTable, 5);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((Gap::Core::igEnumMetaField *)field)->setDefault(g_igFogAttr_modeDefault);
    ((igEnumMetaField *)field)->_getMetaEnumFunction = (int)&IG_GFX_FOG_MODE_GetMetaEnum;
    ((Gap::Core::igFloatMetaField *)(igMetaObject_GetFieldAt(meta, base + 2)))->setDefault(1000.0f);
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    sp[0] = 0.0f;
    sp[3] = 1.0f;
    sp[1] = 0.0f;
    sp[2] = 0.0f;
    igVec4fMetaField_SetDefault((igMetaField *)field2, sp);
    igMetaObject_NameFields(meta, g_igFogAttr_fieldTable, g_igFogAttr_fieldHandles, g_igFogAttr_fieldOffsets, base);
}

