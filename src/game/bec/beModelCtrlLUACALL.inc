igMetaObject *g_beModelCtrlLUACALL_metaObject;
igMetaField *g_beModelCtrlLUACALL_modeNameMetaField;

igMetaObject *beModelCtrlLUACALL_GetMetaObject(void)
{
    igMetaObject *g = g_beModelCtrlLUACALL_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beModelCtrlLUACALL_EnsureRegistered();
    return g_beModelCtrlLUACALL_metaObject;
}

int beModelCtrlLUACALL_GetVTable(void) {
    beModelCtrlLUACALL obj;
    int vtable;
    char **modeNameSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beModelCtrlLUACALL_vtable[0];
    modeNameSlot = (char **)&obj._modeName;
    *modeNameSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlLUACALL_vtable[0];
    igStringRef_Release(modeNameSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlLUACALL_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLUACALL_Register);
}

CallbackArray *beModelCtrlLUACALL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlLUACALL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLUACALL_GetMetaObjectFunction,
        "beModelCtrlLUACALL",
        0x10, /* instance size */
        beModelCtrlLUACALL_GetVTable,
        beModelCtrlLUACALL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlLUACALL_GetMetaObjectFunction(void)
{
    beModelCtrlLUACALL_GetMetaObject();
}

static FieldFactory g_beModelCtrlLUACALL_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beModelCtrlLUACALL_fieldTable[] = {
    "_modeName",
};
static igMetaField **g_beModelCtrlLUACALL_fieldHandles[] = {
    &g_beModelCtrlLUACALL_modeNameMetaField,
};
static int g_beModelCtrlLUACALL_fieldOffsets[] = {
    12,
};

void beModelCtrlLUACALL_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlLUACALL_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlLUACALL_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beModelCtrlLUACALL_fieldTable, g_beModelCtrlLUACALL_fieldHandles, g_beModelCtrlLUACALL_fieldOffsets, base);
}

