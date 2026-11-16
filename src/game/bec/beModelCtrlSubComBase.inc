igMetaObject *g_beModelCtrlSubComBase_metaObject;
igMetaField *g_beModelCtrlSubComBase_isOneSetMetaField;
igMetaField *g_beModelCtrlSubComBase_runFrameMetaField;
igMetaField *g_beModelCtrlSubComBase_startFrameMetaField;

void *beModelCtrlSubComBase_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlSubComBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlSubComBase_EnsureRegistered();
    }
    return g_beModelCtrlSubComBase_metaObject;
}

void beModelCtrlSubComBase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSubComBase_Register);
}

void *beModelCtrlSubComBase_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_beModelCtrlSubComBase_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlSubComBase_GetMetaObjectFunction,
        "beModelCtrlSubComBase",
        0x14, /* instance size */
        0,
        beModelCtrlSubComBase_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSubComBase_GetMetaObjectFunction(void)
{
    beModelCtrlSubComBase_GetMetaObject();
}

static FieldFactory g_beModelCtrlSubComBase_ctorTable[] = {
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beModelCtrlSubComBase_fieldTable[] = {
    "_isOneSet",
    "_runFrame",
    "_startFrame",
};
static igMetaField **g_beModelCtrlSubComBase_fieldHandles[] = {
    &g_beModelCtrlSubComBase_isOneSetMetaField,
    &g_beModelCtrlSubComBase_runFrameMetaField,
    &g_beModelCtrlSubComBase_startFrameMetaField,
};
static int g_beModelCtrlSubComBase_fieldOffsets[] = {
    8,
    12,
    16,
};

void beModelCtrlSubComBase_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlSubComBase_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlSubComBase_ctorTable, 3);
    igFloatMetaField_SetDefault((void *)(((int)igMetaObject_GetFieldAt(meta, base + 1))), 0.0f);
    igMetaObject_NameFields(meta, g_beModelCtrlSubComBase_fieldTable, g_beModelCtrlSubComBase_fieldHandles, g_beModelCtrlSubComBase_fieldOffsets, base);
}

