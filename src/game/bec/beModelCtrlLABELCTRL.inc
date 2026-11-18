igMetaObject *g_beModelCtrlLABELCTRL_metaObject;
igMetaField *g_beModelCtrlLABELCTRL_seqNameMetaField;

void *beModelCtrlLABELCTRL_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlLABELCTRL_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlLABELCTRL_EnsureRegistered();
    }
    return g_beModelCtrlLABELCTRL_metaObject;
}

int beModelCtrlLABELCTRL_GetVTable(void) {
    beModelCtrlLABELCTRL obj;
    int vtable;
    char **seqNameSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beModelCtrlLABELCTRL_vtable[0];
    seqNameSlot = (char **)&obj._seqName;
    *seqNameSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beModelCtrlLABELCTRL_vtable[0];
    igStringRef_Release(seqNameSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlLABELCTRL_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLABELCTRL_Register);
}

CallbackArray *beModelCtrlLABELCTRL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlLABELCTRL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLABELCTRL_GetMetaObjectFunction,
        "beModelCtrlLABELCTRL",
        0x10, /* instance size */
        beModelCtrlLABELCTRL_GetVTable,
        beModelCtrlLABELCTRL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlLABELCTRL_GetMetaObjectFunction(void)
{
    beModelCtrlLABELCTRL_GetMetaObject();
}

static FieldFactory g_beModelCtrlLABELCTRL_ctorTable[] = {
    igStringMetaField_Create,
};
static const char *g_beModelCtrlLABELCTRL_fieldTable[] = {
    "_seqName",
};
static igMetaField **g_beModelCtrlLABELCTRL_fieldHandles[] = {
    &g_beModelCtrlLABELCTRL_seqNameMetaField,
};
static int g_beModelCtrlLABELCTRL_fieldOffsets[] = {
    12,
};

void beModelCtrlLABELCTRL_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlLABELCTRL_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlLABELCTRL_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beModelCtrlLABELCTRL_fieldTable, g_beModelCtrlLABELCTRL_fieldHandles, g_beModelCtrlLABELCTRL_fieldOffsets, base);
}

