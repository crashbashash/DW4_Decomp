igMetaObject *g_beNDMWWindowSelect_metaObject;
igMetaField *g_beNDMWWindowSelect_infoNameMetaField;
igMetaField *g_beNDMWWindowSelect_selectMaxMetaField;
igMetaField *g_beNDMWWindowSelect_offsetPosMetaField;
igMetaField *g_beNDMWWindowSelect_startPointMetaField;
igMetaField *g_beNDMWWindowSelect_isNoCancelMetaField;
igMetaField *g_beNDMWWindowSelect_decideListMetaField;

igMetaObject *FUN_003b58b0(void) {
    if (g_beNDMWWindowSelect_metaObject == 0 || !isValid(g_beNDMWWindowSelect_metaObject)) FUN_003b5900();
    return g_beNDMWWindowSelect_metaObject;
}

void FUN_003b5900(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowSelect_Register);
}

static igMetaObjectCallback g_beNDMWWindowSelect_callbackList[] = { igBoolList_EnsureRegistered, 0 };

void *beNDMWWindowSelect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWWindowSelect_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowSelect_GetMetaObject,
        "beNDMWWindowSelect",
        0x70, /* instance size */
        0,
        beNDMWWindowSelect_InitFields,
        0, /* extra callback item */
        g_beNDMWWindowSelect_callbackList /* callback list */
    );
}

void beNDMWWindowSelect_GetMetaObject(void)
{
    FUN_003b58b0();
}

static FieldFactory g_beNDMWWindowSelect_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    FUN_00187890,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWWindowSelect_fieldTable[] = {
    "_infoName",
    "_selectMax",
    "_offsetPos",
    "_startPoint",
    "_isNoCancel",
    "_decideList",
};
static igMetaField **g_beNDMWWindowSelect_fieldHandles[] = {
    &g_beNDMWWindowSelect_infoNameMetaField,
    &g_beNDMWWindowSelect_selectMaxMetaField,
    &g_beNDMWWindowSelect_offsetPosMetaField,
    &g_beNDMWWindowSelect_startPointMetaField,
    &g_beNDMWWindowSelect_isNoCancelMetaField,
    &g_beNDMWWindowSelect_decideListMetaField,
};
static int g_beNDMWWindowSelect_fieldOffsets[] = {
    80,
    84,
    88,
    100,
    104,
    108,
};

void beNDMWWindowSelect_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWWindowSelect_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWWindowSelect_ctorTable, 6);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 5));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igBoolList_GetOrCreateMetaObject();
    igMetaObject_NameFields(temp_s0, g_beNDMWWindowSelect_fieldTable, g_beNDMWWindowSelect_fieldHandles, g_beNDMWWindowSelect_fieldOffsets, temp_s2);
}

