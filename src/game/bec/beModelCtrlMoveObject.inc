igMetaObject *g_beModelCtrlMoveObject_metaObject;
igMetaField *g_beModelCtrlMoveObject_isRunMetaField;
igMetaField *g_beModelCtrlMoveObject_endTimeMetaField;
igMetaField *g_beModelCtrlMoveObject_modeMetaField;
igMetaField *g_beModelCtrlMoveObject_valueMetaField;
igMetaField *g_beModelCtrlMoveObject_accMetaField;
igMetaField *g_beModelCtrlMoveObject_speedMetaField;
igMetaField *g_beModelCtrlMoveObject_isSeqStopMetaField;
igMetaField *g_beModelCtrlMoveObject_stopValueMetaField;
igMetaField *g_beModelCtrlMoveObject_stopFrameMetaField;

beModelCtrlMoveObject *beModelCtrlMoveObject_Create(int allocator) {
    beModelCtrlMoveObject_EnsureRegistered();
    return (beModelCtrlMoveObject *)igMetaObject_CreateInstance(g_beModelCtrlMoveObject_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beModelCtrlMoveObject_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlMoveObject_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beModelCtrlMoveObject_EnsureRegistered();
    return g_beModelCtrlMoveObject_metaObject;
}

int beModelCtrlMoveObject_GetVTable(void) {
    beModelCtrlMoveObject obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beModelCtrlMoveObject_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlMoveObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMoveObject_Register);
}

CallbackArray *beModelCtrlMoveObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMoveObject_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlMoveObject_GetMetaObjectFunction,
        "beModelCtrlMoveObject",
        0x2c, /* instance size */
        beModelCtrlMoveObject_GetVTable,
        beModelCtrlMoveObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMoveObject_GetMetaObjectFunction(void)
{
    beModelCtrlMoveObject_GetMetaObject();
}

static FieldFactory g_beModelCtrlMoveObject_ctorTable[] = {
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igBoolMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beModelCtrlMoveObject_fieldTable[] = {
    "_isRun",
    "_endTime",
    "_mode",
    "_value",
    "_acc",
    "_speed",
    "_isSeqStop",
    "_stopValue",
    "_stopFrame",
};
static igMetaField **g_beModelCtrlMoveObject_fieldHandles[] = {
    &g_beModelCtrlMoveObject_isRunMetaField,
    &g_beModelCtrlMoveObject_endTimeMetaField,
    &g_beModelCtrlMoveObject_modeMetaField,
    &g_beModelCtrlMoveObject_valueMetaField,
    &g_beModelCtrlMoveObject_accMetaField,
    &g_beModelCtrlMoveObject_speedMetaField,
    &g_beModelCtrlMoveObject_isSeqStopMetaField,
    &g_beModelCtrlMoveObject_stopValueMetaField,
    &g_beModelCtrlMoveObject_stopFrameMetaField,
};
static int g_beModelCtrlMoveObject_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void beModelCtrlMoveObject_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beModelCtrlMoveObject_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlMoveObject_ctorTable, 9);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 1), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 3), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 4), 0.0f);
    igFloatMetaField_SetDefault(igMetaObject_GetFieldAt(meta, base + 5), 0.0f);
    igMetaObject_NameFields(meta, g_beModelCtrlMoveObject_fieldTable, g_beModelCtrlMoveObject_fieldHandles, g_beModelCtrlMoveObject_fieldOffsets, base);
}

