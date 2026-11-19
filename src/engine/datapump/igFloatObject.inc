igMetaObject *g_igFloatObject_metaObject;
igMetaField *g_igFloatObject_valueMetaField;

igMetaObject *igFloatObject_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFloatObject_EnsureRegistered();
    return g_igFloatObject_metaObject;
}

int igFloatObject_GetVTable(void) {
    struct Obj_1e5010 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igFloatObject_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igFloatObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFloatObject_Register);
}

CallbackArray *igFloatObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFloatObject_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igFloatObject_GetMetaObjectFunction,
        "igFloatObject",
        0xC, /* instance size */
        igFloatObject_GetVTable,
        &igFloatObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igFloatObject_GetMetaObjectFunction(void) {
    igFloatObject_GetMetaObject();
}

static FieldFactory g_igFloatObject_ctorTable[] = {
    igFloatMetaField_Create,
};
static const char *g_igFloatObject_fieldTable[] = {
    text_value,
};
static igMetaField **g_igFloatObject_fieldHandles[] = {
    &g_igFloatObject_valueMetaField,
};
static int g_igFloatObject_fieldOffsets[] = {
    8,
};

void igFloatObject_InitFields(void) {
    int firstField;
    igMetaObject *meta;

    meta = g_igFloatObject_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igFloatObject_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igFloatObject_fieldTable, g_igFloatObject_fieldHandles, g_igFloatObject_fieldOffsets, firstField);
}

