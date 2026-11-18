igMetaObject *g_beModelCtrlPDMOVE_metaObject;
igMetaField *g_beModelCtrlPDMOVE_valueMetaField;
igMetaField *g_beModelCtrlPDMOVE_frameMetaField;

void *beModelCtrlPDMOVE_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlPDMOVE_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlPDMOVE_EnsureRegistered();
    }
    return g_beModelCtrlPDMOVE_metaObject;
}

int beModelCtrlPDMOVE_GetVTable(void) {
    beModelCtrlPDMOVE obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlPDMOVE_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlPDMOVE_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlPDMOVE_Register);
}

CallbackArray *beModelCtrlPDMOVE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlPDMOVE_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlPDMOVE_GetMetaObjectFunction,
        "beModelCtrlPDMOVE",
        0x14, /* instance size */
        beModelCtrlPDMOVE_GetVTable,
        beModelCtrlPDMOVE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlPDMOVE_GetMetaObjectFunction(void)
{
    beModelCtrlPDMOVE_GetMetaObject();
}

static FieldFactory g_beModelCtrlPDMOVE_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beModelCtrlPDMOVE_fieldTable[] = {
    "_value",
    "_frame",
};
static igMetaField **g_beModelCtrlPDMOVE_fieldHandles[] = {
    &g_beModelCtrlPDMOVE_valueMetaField,
    &g_beModelCtrlPDMOVE_frameMetaField,
};
static int g_beModelCtrlPDMOVE_fieldOffsets[] = {
    12,
    16,
};

void beModelCtrlPDMOVE_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlPDMOVE_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlPDMOVE_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beModelCtrlPDMOVE_fieldTable, g_beModelCtrlPDMOVE_fieldHandles, g_beModelCtrlPDMOVE_fieldOffsets, base);
}

