igMetaObject *g_beModelCtrlMOVEEX_metaObject;
igMetaField *g_beModelCtrlMOVEEX_valueMetaField;
igMetaField *g_beModelCtrlMOVEEX_frameMetaField;
igMetaField *g_beModelCtrlMOVEEX_playTimeMetaField;
igMetaField *g_beModelCtrlMOVEEX_isSeqStopMetaField;
igMetaField *g_beModelCtrlMOVEEX_stopValueMetaField;
igMetaField *g_beModelCtrlMOVEEX_stopFrameMetaField;

void *beModelCtrlMOVEEX_GetMetaObject(void) {
    bool ok;
    if (g_beModelCtrlMOVEEX_metaObject == 0) goto make;
    ok = !!(g_beModelCtrlMOVEEX_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beModelCtrlMOVEEX_EnsureRegistered();
done:;
    return g_beModelCtrlMOVEEX_metaObject;
}

int beModelCtrlMOVEEX_GetVTable(void) {
    beModelCtrlMOVEEX obj;
    int vtable;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    obj._vtable = (int)&g_beModelCtrlMOVEEX_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beModelCtrlMOVEEX_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVEEX_Register);
}

void *beModelCtrlMOVEEX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMOVEEX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVEEX_GetMetaObjectFunction,
        "beModelCtrlMOVEEX",
        0x24, /* instance size */
        beModelCtrlMOVEEX_GetVTable,
        beModelCtrlMOVEEX_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMOVEEX_GetMetaObjectFunction(void)
{
    beModelCtrlMOVEEX_GetMetaObject();
}

static FieldFactory g_beModelCtrlMOVEEX_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beModelCtrlMOVEEX_fieldTable[] = {
    "_value",
    "_frame",
    "_playTime",
    "_isSeqStop",
    "_stopValue",
    "_stopFrame",
};
static igMetaField **g_beModelCtrlMOVEEX_fieldHandles[] = {
    &g_beModelCtrlMOVEEX_valueMetaField,
    &g_beModelCtrlMOVEEX_frameMetaField,
    &g_beModelCtrlMOVEEX_playTimeMetaField,
    &g_beModelCtrlMOVEEX_isSeqStopMetaField,
    &g_beModelCtrlMOVEEX_stopValueMetaField,
    &g_beModelCtrlMOVEEX_stopFrameMetaField,
};
static int g_beModelCtrlMOVEEX_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
};

void beModelCtrlMOVEEX_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlMOVEEX_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlMOVEEX_ctorTable, 6);
    igMetaObject_NameFields(meta, g_beModelCtrlMOVEEX_fieldTable, g_beModelCtrlMOVEEX_fieldHandles, g_beModelCtrlMOVEEX_fieldOffsets, base);
}

