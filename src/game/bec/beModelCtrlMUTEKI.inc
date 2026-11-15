igMetaObject *g_beModelCtrlMUTEKI_metaObject;
igMetaField *g_beModelCtrlMUTEKI_frameMetaField;

igMetaObject *FUN_00354ca0(void) {
    igMetaObject *g = g_beModelCtrlMUTEKI_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_00354d80();
    return g_beModelCtrlMUTEKI_metaObject;
}

int beModelCtrlMUTEKI_GetVTable(void) {
    union U_354cf0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00537770[0];
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

void FUN_00354d80(void)
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
        beModelCtrlMUTEKI_GetMetaObject,
        "beModelCtrlMUTEKI",
        0x10, /* instance size */
        beModelCtrlMUTEKI_GetVTable,
        beModelCtrlMUTEKI_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMUTEKI_GetMetaObject(void)
{
    FUN_00354ca0();
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
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlMUTEKI_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beModelCtrlMUTEKI_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beModelCtrlMUTEKI_fieldTable, g_beModelCtrlMUTEKI_fieldHandles, g_beModelCtrlMUTEKI_fieldOffsets, temp_s1);
}

