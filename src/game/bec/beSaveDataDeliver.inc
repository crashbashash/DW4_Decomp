igMetaObject *g_beSaveDataDeliver_metaObject;
igMetaField *g_beSaveDataDeliver_sizeMetaField;
igMetaField *g_beSaveDataDeliver_dataMetaField;

igMetaObject *FUN_0034aeb0(void) {
    if (g_beSaveDataDeliver_metaObject == 0) {
        g_beSaveDataDeliver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSaveDataDeliver_metaObject;
}

igMetaObject *FUN_0034af00(void) {
    igMetaObject *g = g_beSaveDataDeliver_metaObject;
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0034af90();
done:
    return g_beSaveDataDeliver_metaObject;
}

int beSaveDataDeliver_GetVTable(void) {
    struct Obj_34af50 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538910[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034af90(void)
{
    igMetaObject_RunStaticInit(beSaveDataDeliver_Register);
}

void *beSaveDataDeliver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveDataDeliver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveDataDeliver_GetMetaObject,
        "beSaveDataDeliver",
        0x10, /* instance size */
        beSaveDataDeliver_GetVTable,
        beSaveDataDeliver_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveDataDeliver_GetMetaObject(void)
{
    FUN_0034af00();
}

static FieldFactory g_beSaveDataDeliver_ctorTable[] = {
    igIntMetaField_Create,
    igMemoryRefMetaField_Create,
};
static const char *g_beSaveDataDeliver_fieldTable[] = {
    "_size",
    "_data",
};
static igMetaField **g_beSaveDataDeliver_fieldHandles[] = {
    &g_beSaveDataDeliver_sizeMetaField,
    &g_beSaveDataDeliver_dataMetaField,
};
static int g_beSaveDataDeliver_fieldOffsets[] = {
    12,
    8,
};

void beSaveDataDeliver_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSaveDataDeliver_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSaveDataDeliver_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, g_beSaveDataDeliver_fieldTable, g_beSaveDataDeliver_fieldHandles, g_beSaveDataDeliver_fieldOffsets, temp_s2);
}

