igMetaObject *g_beSaveIntfComMdlData_metaObject;
igMetaField *g_beSaveIntfComMdlData_ramNoMetaField;
igMetaField *g_beSaveIntfComMdlData_openSQMetaField;
igMetaField *g_beSaveIntfComMdlData_infoNameMetaField;

void *FUN_003bc710(void) {
    igMetaObject *g = g_beSaveIntfComMdlData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bc820();
    }
    return g_beSaveIntfComMdlData_metaObject;
}

int beSaveIntfComMdlData_GetVTable(void) {
    Obj_3bc760 obj;
    int r;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&DAT_0053d830[0];
    obj._openSQ = 0;
    obj._infoName = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&DAT_0053d830[0];
    obj.rel16();
    obj.rel12();
    return r;
}

void FUN_003bc820(void)
{
    igMetaObject_RunStaticInit(beSaveIntfComMdlData_Register);
}

void *beSaveIntfComMdlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveIntfComMdlData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveIntfComMdlData_GetMetaObject,
        "beSaveIntfComMdlData",
        0x14, /* instance size */
        beSaveIntfComMdlData_GetVTable,
        beSaveIntfComMdlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveIntfComMdlData_GetMetaObject(void)
{
    FUN_003bc710();
}

static FieldFactory g_beSaveIntfComMdlData_ctorTable[] = {
    igIntMetaField_Create,
    igStringMetaField_Create,
    igStringMetaField_Create,
};
static const char *g_beSaveIntfComMdlData_fieldTable[] = {
    "_ramNo",
    "_openSQ",
    "_infoName",
};
static igMetaField **g_beSaveIntfComMdlData_fieldHandles[] = {
    &g_beSaveIntfComMdlData_ramNoMetaField,
    &g_beSaveIntfComMdlData_openSQMetaField,
    &g_beSaveIntfComMdlData_infoNameMetaField,
};
static int g_beSaveIntfComMdlData_fieldOffsets[] = {
    8,
    12,
    16,
};

void beSaveIntfComMdlData_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beSaveIntfComMdlData_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSaveIntfComMdlData_ctorTable, 3);
    igMetaObject_NameFields(temp_s0, g_beSaveIntfComMdlData_fieldTable, g_beSaveIntfComMdlData_fieldHandles, g_beSaveIntfComMdlData_fieldOffsets, temp_s1);
}

