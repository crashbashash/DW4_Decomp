igMetaObject *g_beModelCtrlAIData_metaObject;
igMetaField *g_beModelCtrlAIData_dirRadianMetaField;
igMetaField *g_beModelCtrlAIData_timeMetaField;
igMetaField *g_beModelCtrlAIData_limitMetaField;

void *beModelCtrlAIData_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlAIData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlAIData_EnsureRegistered();
    }
    return g_beModelCtrlAIData_metaObject;
}

int beModelCtrlAIData_GetVTable(void) {
    beModelCtrlAIData obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlAIData_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlAIData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIData_Register);
}

void *beModelCtrlAIData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlAIData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlAIData_GetMetaObjectFunction,
        "beModelCtrlAIData",
        0x18, /* instance size */
        beModelCtrlAIData_GetVTable,
        beModelCtrlAIData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlAIData_GetMetaObjectFunction(void)
{
    beModelCtrlAIData_GetMetaObject();
}

static FieldFactory g_beModelCtrlAIData_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beModelCtrlAIData_fieldTable[] = {
    "_dirRadian",
    "_time",
    "_limit",
};
static igMetaField **g_beModelCtrlAIData_fieldHandles[] = {
    &g_beModelCtrlAIData_dirRadianMetaField,
    &g_beModelCtrlAIData_timeMetaField,
    &g_beModelCtrlAIData_limitMetaField,
};
static int g_beModelCtrlAIData_fieldOffsets[] = {
    12,
    16,
    20,
};

void beModelCtrlAIData_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlAIData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlAIData_ctorTable, 3);
    igMetaObject_NameFields(meta, g_beModelCtrlAIData_fieldTable, g_beModelCtrlAIData_fieldHandles, g_beModelCtrlAIData_fieldOffsets, base);
}

