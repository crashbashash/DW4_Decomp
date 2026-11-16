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
    int *q1;
    int *q2;
    char *o;
    int *a1;
    int v0;
    int t;

    igObject_InitHeader(&obj);
    q1 = &obj._resetCondition;
    q2 = &obj._callLuaFile;
    obj._vtable = (int)&g_beTimerData_vtable[0];
    obj._resetCondition = 0;
    obj._callLuaFile = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beTimerData_vtable[0];
    if (q2 != 0) {
        o = (char *)*q2;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (q1 != 0) {
        o = (char *)*q1;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return t;
}

void beTimerData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTimerData_Register);
}

void *beTimerData_Register(void) {
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
    void *meta;

    meta = (void *)g_beTimerData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTimerData_ctorTable, 4);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, base + 1)), 0);
    igStringMetaField_SetDefaultText(((int)igMetaObject_GetFieldAt(meta, base + 2)), 0);
    igMetaObject_NameFields(meta, g_beTimerData_fieldTable, g_beTimerData_fieldHandles, g_beTimerData_fieldOffsets, base);
}

