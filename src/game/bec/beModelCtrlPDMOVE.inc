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
    union U_355210 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beModelCtrlPDMOVE_vtable[0];
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

void beModelCtrlPDMOVE_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlPDMOVE_Register);
}

void *beModelCtrlPDMOVE_Register(void) {
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
    void *meta;

    meta = (void *)g_beModelCtrlPDMOVE_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beModelCtrlPDMOVE_ctorTable, 2);
    igMetaObject_NameFields(meta, g_beModelCtrlPDMOVE_fieldTable, g_beModelCtrlPDMOVE_fieldHandles, g_beModelCtrlPDMOVE_fieldOffsets, base);
}

