igMetaObject *g_beTimerData_metaObject;
igMetaField *g_beTimerData_startTimeMetaField;
igMetaField *g_beTimerData_resetConditionMetaField;
igMetaField *g_beTimerData_callLuaFileMetaField;
igMetaField *g_beTimerData_downTimerMetaField;

igMetaObject *beTimerData_GetMetaObject(void)
{
    igMetaObject *g = g_beTimerData_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beTimerData_EnsureRegistered();
    return g_beTimerData_metaObject;
}

int beTimerData_GetVTable(void) {
    beTimerData obj;
    int vtable;
    char **resetConditionSlot;
    char **callLuaFileSlot;

    igObject_InitHeader(&obj);
    callLuaFileSlot = (char **)&obj._callLuaFile;
    resetConditionSlot = (char **)&obj._resetCondition;
    obj._vtable = (int)&g_beTimerData_vtable[0];
    *resetConditionSlot = 0;
    *callLuaFileSlot = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
    obj._vtable = (int)&g_beTimerData_vtable[0];
    igStringRef_Release(callLuaFileSlot);
    igStringRef_Release(resetConditionSlot);
    return vtable;
}

void beTimerData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTimerData_Register);
}

CallbackArray *beTimerData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTimerData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beTimerData_GetMetaObjectFunction,
        "beTimerData",
        0x20, /* instance size */
        beTimerData_GetVTable,
        beTimerData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beTimerData_GetMetaObjectFunction(void)
{
    beTimerData_GetMetaObject();
}

static FieldFactory g_beTimerData_ctorTable[] = {
    igLongMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_beTimerData_fieldTable[] = {
    "_startTime",
    "_resetCondition",
    "_callLuaFile",
    "_downTimer",
};
static igMetaField **g_beTimerData_fieldHandles[] = {
    &g_beTimerData_startTimeMetaField,
    &g_beTimerData_resetConditionMetaField,
    &g_beTimerData_callLuaFileMetaField,
    &g_beTimerData_downTimerMetaField,
};
static int g_beTimerData_fieldOffsets[] = {
    8,
    16,
    20,
    24,
};

void beTimerData_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beTimerData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTimerData_ctorTable, 4);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, base + 1)), 0);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, base + 2)), 0);
    igMetaObject_NameFields(meta, g_beTimerData_fieldTable, g_beTimerData_fieldHandles, g_beTimerData_fieldOffsets, base);
}

