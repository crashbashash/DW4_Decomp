igMetaObject *g_igFloatObject_metaObject;
igMetaField *g_igFloatObject_valueMetaField;

igMetaObject *igFloatObject_GetMetaObject(void)
{
    igMetaObject *g = g_igFloatObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e5050();
    return g_igFloatObject_metaObject;
}

int igFloatObject_GetVTable(void) {
    struct Obj_1e5010 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bb50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001e5050(void)
{
    igMetaObject_RunStaticInit(igFloatObject_Register);
}

void igFloatObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igFloatObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igFloatObject_GetMetaObject,
        "igFloatObject",
        0xC, /* instance size */
        igFloatObject_GetVTable,
        &igFloatObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igFloatObject_GetMetaObject(void) {
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
    firstField = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igFloatObject_ctorTable, 1);
    igMetaObject_NameFields(meta, g_igFloatObject_fieldTable, g_igFloatObject_fieldHandles, g_igFloatObject_fieldOffsets, firstField);
}

