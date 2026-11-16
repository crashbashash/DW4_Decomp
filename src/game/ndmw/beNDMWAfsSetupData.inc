igMetaObject *g_beNDMWAfsSetupData_metaObject;
igMetaField *g_beNDMWAfsSetupData_fileCountMetaField;

void *beNDMWAfsSetupData_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWAfsSetupData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWAfsSetupData_EnsureRegistered();
    }
    return g_beNDMWAfsSetupData_metaObject;
}

int beNDMWAfsSetupData_GetVTable(void) {
    union U_3ca9e0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beNDMWAfsSetupData_vtable[0];
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

void beNDMWAfsSetupData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupData_Register);
}

void *beNDMWAfsSetupData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWAfsSetupData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beNDMWAfsSetupData_GetMetaObject,
        "beNDMWAfsSetupData",
        0x10, /* instance size */
        beNDMWAfsSetupData_GetVTable,
        beNDMWAfsSetupData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWAfsSetupData_GetMetaObject(void)
{
    beNDMWAfsSetupData_ResolveMetaObject();
}

static FieldFactory g_beNDMWAfsSetupData_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWAfsSetupData_fieldTable[] = {
    "_fileCount",
};
static igMetaField **g_beNDMWAfsSetupData_fieldHandles[] = {
    &g_beNDMWAfsSetupData_fileCountMetaField,
};
static int g_beNDMWAfsSetupData_fieldOffsets[] = {
    12,
};

void beNDMWAfsSetupData_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWAfsSetupData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWAfsSetupData_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWAfsSetupData_fieldTable, g_beNDMWAfsSetupData_fieldHandles, g_beNDMWAfsSetupData_fieldOffsets, base);
}

