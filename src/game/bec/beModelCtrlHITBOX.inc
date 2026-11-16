igMetaObject *g_beModelCtrlHITBOX_metaObject;
igMetaField *g_beModelCtrlHITBOX_kindMetaField;
igMetaField *g_beModelCtrlHITBOX_startMetaField;
igMetaField *g_beModelCtrlHITBOX_lengthMetaField;
igMetaField *g_beModelCtrlHITBOX_offsetMetaField;
igMetaField *g_beModelCtrlHITBOX_boxSizeMetaField;

void beModelCtrlHITBOX_Create(int allocator) {
    beModelCtrlHITBOX_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x588D20, allocator);
}

igMetaObject *beModelCtrlHITBOX_GetMetaObject(void)
{
    igMetaObject *g = g_beModelCtrlHITBOX_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beModelCtrlHITBOX_EnsureRegistered();
    return g_beModelCtrlHITBOX_metaObject;
}

int beModelCtrlHITBOX_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beModelCtrlHITBOX_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void beModelCtrlHITBOX_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlHITBOX_Register);
}

void *beModelCtrlHITBOX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlHITBOX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlHITBOX_GetMetaObjectFunction,
        "beModelCtrlHITBOX",
        0x30, /* instance size */
        beModelCtrlHITBOX_GetVTable,
        beModelCtrlHITBOX_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlHITBOX_GetMetaObjectFunction(void)
{
    beModelCtrlHITBOX_GetMetaObject();
}

static FieldFactory g_beModelCtrlHITBOX_ctorTable[] = {
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    FUN_00187890,
    FUN_00187890,
};
static const char *g_beModelCtrlHITBOX_fieldTable[] = {
    "_kind",
    "_start",
    "_length",
    "_offset",
    "_boxSize",
};
static igMetaField **g_beModelCtrlHITBOX_fieldHandles[] = {
    &g_beModelCtrlHITBOX_kindMetaField,
    &g_beModelCtrlHITBOX_startMetaField,
    &g_beModelCtrlHITBOX_lengthMetaField,
    &g_beModelCtrlHITBOX_offsetMetaField,
    &g_beModelCtrlHITBOX_boxSizeMetaField,
};
static int g_beModelCtrlHITBOX_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    36,
};

void beModelCtrlHITBOX_InitFields(void) {
    int base;
    void *meta;

    meta = (void *)g_beModelCtrlHITBOX_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlHITBOX_ctorTable, 5);
    igMetaObject_NameFields(meta, g_beModelCtrlHITBOX_fieldTable, g_beModelCtrlHITBOX_fieldHandles, g_beModelCtrlHITBOX_fieldOffsets, base);
}

