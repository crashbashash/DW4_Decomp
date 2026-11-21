igMetaObject *g_beNDMWWindowSelect_metaObject;
igMetaField *g_beNDMWWindowSelect_infoNameMetaField;
igMetaField *g_beNDMWWindowSelect_selectMaxMetaField;
igMetaField *g_beNDMWWindowSelect_offsetPosMetaField;
igMetaField *g_beNDMWWindowSelect_startPointMetaField;
igMetaField *g_beNDMWWindowSelect_isNoCancelMetaField;
igMetaField *g_beNDMWWindowSelect_decideListMetaField;

igMetaObject *beNDMWWindowSelect_GetMetaObject(void) {
    if (g_beNDMWWindowSelect_metaObject == 0 || !isValid(g_beNDMWWindowSelect_metaObject)) beNDMWWindowSelect_EnsureRegistered();
    return g_beNDMWWindowSelect_metaObject;
}

void beNDMWWindowSelect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWWindowSelect_Register);
}

static igMetaObjectCallback g_beNDMWWindowSelect_callbackList[] = { Gap::Core::igBoolList::arkRegister, 0 };

CallbackArray *beNDMWWindowSelect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beNDMWWindowSelect_metaObject,
        beNDMWWindow_Register,
        beNDMWWindow_GetPublishedMetaObject,
        beNDMWWindowSelect_GetMetaObjectFunction,
        "beNDMWWindowSelect",
        0x70, /* instance size */
        0,
        beNDMWWindowSelect_InitFields,
        0, /* extra callback item */
        g_beNDMWWindowSelect_callbackList /* callback list */
    );
}

void beNDMWWindowSelect_GetMetaObjectFunction(void)
{
    beNDMWWindowSelect_GetMetaObject();
}

static FieldFactory g_beNDMWWindowSelect_ctorTable[] = {
    igStringMetaField_Create,
    igIntMetaField_Create,
    (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool,
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
    int base;
    void *decideList;
    igMetaObject *meta;

    meta = g_beNDMWWindowSelect_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWWindowSelect_ctorTable, 6);
    decideList = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)decideList)->_metaObject = (int)Gap::Core::igBoolList::getClassTypeLazy();
    igMetaObject_NameFields(meta, g_beNDMWWindowSelect_fieldTable, g_beNDMWWindowSelect_fieldHandles, g_beNDMWWindowSelect_fieldOffsets, base);
}

