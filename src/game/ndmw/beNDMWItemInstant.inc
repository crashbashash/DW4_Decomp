igMetaObject *g_beNDMWItemInstant_metaObject;
igMetaField *g_beNDMWItemInstant_valueMetaField;

void FUN_003c83c0(int arg0) {
    FUN_003c8490();
    igMetaObject_CreateInstance(g_beNDMWItemInstant_metaObject, arg0);
}

igMetaObject *beNDMWItemInstant_GetReadyMetaObject(void) {
    if (g_beNDMWItemInstant_metaObject == 0 || !isValid(g_beNDMWItemInstant_metaObject)) FUN_003c8490();
    return g_beNDMWItemInstant_metaObject;
}

int beNDMWItemInstant_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00540730[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c8490(void)
{
    igMetaObject_RunStaticInit(beNDMWItemInstant_Register);
}

void *beNDMWItemInstant_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemInstant_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemInstant_GetMetaObject,
        "beNDMWItemInstant",
        0x18, /* instance size */
        beNDMWItemInstant_GetVTable,
        beNDMWItemInstant_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemInstant_GetMetaObject(void)
{
    beNDMWItemInstant_GetReadyMetaObject();
}

static FieldFactory g_beNDMWItemInstant_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWItemInstant_fieldTable[] = {
    "_value",
};
static igMetaField **g_beNDMWItemInstant_fieldHandles[] = {
    &g_beNDMWItemInstant_valueMetaField,
};
static int g_beNDMWItemInstant_fieldOffsets[] = {
    20,
};

void beNDMWItemInstant_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWItemInstant_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWItemInstant_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWItemInstant_fieldTable, g_beNDMWItemInstant_fieldHandles, g_beNDMWItemInstant_fieldOffsets, temp_s1);
}

