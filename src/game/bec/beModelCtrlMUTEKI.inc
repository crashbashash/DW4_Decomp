igMetaObject *g_beModelCtrlMUTEKI_metaObject;
igMetaField *g_beModelCtrlMUTEKI_frameMetaField;

igMetaObject *beModelCtrlMUTEKI_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlMUTEKI_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beModelCtrlMUTEKI_EnsureRegistered();
    return g_beModelCtrlMUTEKI_metaObject;
}

int beModelCtrlMUTEKI_GetVTable(void) {
    beModelCtrlMUTEKI obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlMUTEKI_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlMUTEKI_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMUTEKI_Register);
}

void *beModelCtrlMUTEKI_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMUTEKI_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMUTEKI_GetMetaObjectFunction,
        "beModelCtrlMUTEKI",
        0x10, /* instance size */
        beModelCtrlMUTEKI_GetVTable,
        beModelCtrlMUTEKI_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMUTEKI_GetMetaObjectFunction(void)
{
    beModelCtrlMUTEKI_GetMetaObject();
}

static FieldFactory g_beModelCtrlMUTEKI_ctorTable[] = {
    igFloatMetaField_Create,
};
static const char *g_beModelCtrlMUTEKI_fieldTable[] = {
    "_frame",
};
static igMetaField **g_beModelCtrlMUTEKI_fieldHandles[] = {
    &g_beModelCtrlMUTEKI_frameMetaField,
};
static int g_beModelCtrlMUTEKI_fieldOffsets[] = {
    12,
};

void beModelCtrlMUTEKI_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlMUTEKI_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlMUTEKI_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beModelCtrlMUTEKI_fieldTable, g_beModelCtrlMUTEKI_fieldHandles, g_beModelCtrlMUTEKI_fieldOffsets, base);
}

