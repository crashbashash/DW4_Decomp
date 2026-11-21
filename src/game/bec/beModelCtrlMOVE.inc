igMetaObject *g_beModelCtrlMOVE_metaObject;
igMetaField *g_beModelCtrlMOVE_valueMetaField;
igMetaField *g_beModelCtrlMOVE_frameMetaField;

void *beModelCtrlMOVE_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlMOVE_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlMOVE_EnsureRegistered();
    }
    return g_beModelCtrlMOVE_metaObject;
}

int beModelCtrlMOVE_GetVTable(void) {
    beModelCtrlMOVE obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlMOVE_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlMOVE_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVE_Register);
}

CallbackArray *beModelCtrlMOVE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMOVE_metaObject,
        Gap::Core::igNamedObject::arkRegisterInternal,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVE_GetMetaObjectFunction,
        "beModelCtrlMOVE",
        0x14, /* instance size */
        beModelCtrlMOVE_GetVTable,
        beModelCtrlMOVE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMOVE_GetMetaObjectFunction(void)
{
    beModelCtrlMOVE_GetMetaObject();
}

static FieldFactory g_beModelCtrlMOVE_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beModelCtrlMOVE_fieldTable[] = {
    "_value",
    "_frame",
};
static igMetaField **g_beModelCtrlMOVE_fieldHandles[] = {
    &g_beModelCtrlMOVE_valueMetaField,
    &g_beModelCtrlMOVE_frameMetaField,
};
static int g_beModelCtrlMOVE_fieldOffsets[] = {
    12,
    16,
};

void beModelCtrlMOVE_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlMOVE_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlMOVE_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beModelCtrlMOVE_fieldTable, g_beModelCtrlMOVE_fieldHandles, g_beModelCtrlMOVE_fieldOffsets, base);
}

