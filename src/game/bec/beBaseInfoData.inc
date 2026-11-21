igMetaObject *g_beBaseInfoData_metaObject;
igMetaField *g_beBaseInfoData_versionMetaField;

void *beBaseInfoData_GetMetaObject(void) {
    igMetaObject *g = g_beBaseInfoData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBaseInfoData_EnsureRegistered();
    }
    return g_beBaseInfoData_metaObject;
}

void beBaseInfoData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBaseInfoData_Register);
}

CallbackArray *beBaseInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beBaseInfoData_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        beBaseInfoData_GetMetaObjectFunction,
        "beBaseInfoData",
        0x10, /* instance size */
        0,
        beBaseInfoData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBaseInfoData_GetMetaObjectFunction(void)
{
    beBaseInfoData_GetMetaObject();
}

static FieldFactory g_beBaseInfoData_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beBaseInfoData_fieldTable[] = {
    "_version",
};
static igMetaField **g_beBaseInfoData_fieldHandles[] = {
    &g_beBaseInfoData_versionMetaField,
};
static int g_beBaseInfoData_fieldOffsets[] = {
    12,
};

void beBaseInfoData_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beBaseInfoData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBaseInfoData_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beBaseInfoData_fieldTable, g_beBaseInfoData_fieldHandles, g_beBaseInfoData_fieldOffsets, base);
}

