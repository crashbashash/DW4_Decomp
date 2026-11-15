igMetaObject *g_beModelCtrlAIData_metaObject;
igMetaField *g_beModelCtrlAIData_dirRadianMetaField;
igMetaField *g_beModelCtrlAIData_timeMetaField;
igMetaField *g_beModelCtrlAIData_limitMetaField;

void *FUN_00354860(void) {
    igMetaObject *g = g_beModelCtrlAIData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00354940();
    }
    return g_beModelCtrlAIData_metaObject;
}

int beModelCtrlAIData_GetVTable(void) {
    union U_3548b0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00537830[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void FUN_00354940(void)
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
        beModelCtrlAIData_GetMetaObject,
        "beModelCtrlAIData",
        0x18, /* instance size */
        beModelCtrlAIData_GetVTable,
        beModelCtrlAIData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlAIData_GetMetaObject(void)
{
    FUN_00354860();
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
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlAIData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlAIData_ctorTable, 3);
    igMetaObject_NameFields(temp_s0, g_beModelCtrlAIData_fieldTable, g_beModelCtrlAIData_fieldHandles, g_beModelCtrlAIData_fieldOffsets, temp_s1);
}

