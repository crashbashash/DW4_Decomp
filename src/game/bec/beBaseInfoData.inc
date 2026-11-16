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

void *beBaseInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beBaseInfoData_metaObject,
        igNamedObject_Register,
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
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfoData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beBaseInfoData_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beBaseInfoData_fieldTable, g_beBaseInfoData_fieldHandles, g_beBaseInfoData_fieldOffsets, temp_s1);
}

