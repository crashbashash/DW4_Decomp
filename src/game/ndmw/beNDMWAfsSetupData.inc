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
    beNDMWAfsSetupData obj;
    int vtable;
    int *nameRef;

    igObject_InitHeader(&obj);
    nameRef = &obj._name;
    *nameRef = 0;
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    *(int **)&obj._vtable = &g_beNDMWAfsSetupData_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWAfsSetupData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupData_Register);
}

CallbackArray *beNDMWAfsSetupData_Register(void) {
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

