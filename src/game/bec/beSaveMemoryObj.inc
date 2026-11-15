igMetaObject *g_beSaveMemoryObj_metaObject;
igMetaField *g_beSaveMemoryObj_memMetaField;

void beSaveMemoryObj_CreateInstance(int arg0) {
    FUN_0034ad70();
    igMetaObject_CreateInstance(*(int *)0x5883A0, arg0);
}

igMetaObject *FUN_0034ac90(void) {
    if (g_beSaveMemoryObj_metaObject == 0) {
        g_beSaveMemoryObj_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSaveMemoryObj_metaObject;
}

igMetaObject *FUN_0034ace0(void) {
    igMetaObject *g = g_beSaveMemoryObj_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0034ad70();
    return g_beSaveMemoryObj_metaObject;
}

int beSaveMemoryObj_GetVTable(void) {
    struct Obj_34ad30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c0e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0034ad70(void)
{
    igMetaObject_RunStaticInit(beSaveMemoryObj_Register);
}

void *beSaveMemoryObj_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveMemoryObj_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSaveMemoryObj_GetMetaObject,
        "beSaveMemoryObj",
        0xc, /* instance size */
        beSaveMemoryObj_GetVTable,
        beSaveMemoryObj_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beSaveMemoryObj_GetMetaObject(void)
{
    FUN_0034ace0();
}

static FieldFactory g_beSaveMemoryObj_ctorTable[] = {
    igMemoryRefMetaField_Create,
};
static const char *g_beSaveMemoryObj_fieldTable[] = {
    "_mem",
};
static igMetaField **g_beSaveMemoryObj_fieldHandles[] = {
    &g_beSaveMemoryObj_memMetaField,
};
static int g_beSaveMemoryObj_fieldOffsets[] = {
    8,
};

void beSaveMemoryObj_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beSaveMemoryObj_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beSaveMemoryObj_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = igCharMetaField_GetDefaultDescriptor();
    igMetaObject_NameFields(temp_s0, g_beSaveMemoryObj_fieldTable, g_beSaveMemoryObj_fieldHandles, g_beSaveMemoryObj_fieldOffsets, temp_s2);
}

