igMetaObject *g_beCriVolume_metaObject;
igMetaField *g_beCriVolume_isExecMetaField;
igMetaField *g_beCriVolume_maxMetaField;
igMetaField *g_beCriVolume_currentMetaField;
igMetaField *g_beCriVolume_staMetaField;
igMetaField *g_beCriVolume_endMetaField;
igMetaField *g_beCriVolume_unitMetaField;

igMetaObject *FUN_00366340(void) {
    if (g_beCriVolume_metaObject == 0) {
        g_beCriVolume_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beCriVolume_metaObject;
}

igMetaObject *FUN_00366390(void) {
    igMetaObject *g = g_beCriVolume_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00366420();
done:
    return g_beCriVolume_metaObject;
}

int beCriVolume_GetVTable(void) {
    struct Obj_3663e0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535090[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00366420(void)
{
    igMetaObject_RunStaticInit(beCriVolume_Register);
}

void *beCriVolume_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCriVolume_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCriVolume_GetMetaObject,
        "beCriVolume",
        0x20, /* instance size */
        beCriVolume_GetVTable,
        beCriVolume_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beCriVolume_GetMetaObject(void)
{
    FUN_00366390();
}

static FieldFactory g_beCriVolume_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
};
static const char *g_beCriVolume_fieldTable[] = {
    "_isExec",
    "_max",
    "_current",
    "_sta",
    "_end",
    "_unit",
};
static igMetaField **g_beCriVolume_fieldHandles[] = {
    &g_beCriVolume_isExecMetaField,
    &g_beCriVolume_maxMetaField,
    &g_beCriVolume_currentMetaField,
    &g_beCriVolume_staMetaField,
    &g_beCriVolume_endMetaField,
    &g_beCriVolume_unitMetaField,
};
static int g_beCriVolume_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void beCriVolume_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beCriVolume_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beCriVolume_ctorTable, 6);
    igMetaObject_NameFields(temp_s0, g_beCriVolume_fieldTable, g_beCriVolume_fieldHandles, g_beCriVolume_fieldOffsets, temp_s1);
}

