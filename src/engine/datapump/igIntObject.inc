igMetaObject *g_igIntObject_metaObject;
igMetaField *g_igIntObject_valueMetaField;

igMetaObject *igIntObject_GetMetaObject(void)
{
    igMetaObject *g = g_igIntObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4ec0();
    return g_igIntObject_metaObject;
}

int igIntObject_GetVTable(void) {
    struct Obj_1e4e80 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igIntObject_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void FUN_001e4ec0(void)
{
    igMetaObject_RunStaticInit(igIntObject_Register);
}

CallbackArray *igIntObject_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igIntObject_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igIntObject_GetMetaObject,
        "igIntObject",
        0xC, /* instance size */
        igIntObject_GetVTable,
        &igIntObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igIntObject_GetMetaObject(void) {
    igIntObject_GetMetaObject();
}

static FieldFactory g_igIntObject_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_igIntObject_fieldTable[] = {
    text_value,
};
static igMetaField **g_igIntObject_fieldHandles[] = {
    &g_igIntObject_valueMetaField,
};
static int g_igIntObject_fieldOffsets[] = {
    8,
};

void igIntObject_InitFields(void) {
    int firstField;
    igMetaObject *meta;

    meta = g_igIntObject_metaObject;
    firstField = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igIntObject_ctorTable, 1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igIntObject_fieldTable, g_igIntObject_fieldHandles, g_igIntObject_fieldOffsets, firstField);
}

