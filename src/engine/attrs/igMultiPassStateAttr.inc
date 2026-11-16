igMetaObject *g_igMultiPassStateAttr_metaObject;
igMetaField *g_igMultiPassStateAttr_numPassesMetaField;

void FUN_00135190(int arg0) {
    FUN_001352b0();
    igMetaObject_CreateInstance(*(int *)0x55EFD0, arg0);
}

igMetaObject *FUN_001351d0(void) {
    if (g_igMultiPassStateAttr_metaObject == 0) {
        g_igMultiPassStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMultiPassStateAttr_metaObject;
}

igMetaObject *igMultiPassStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMultiPassStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001352b0();
    return g_igMultiPassStateAttr_metaObject;
}

int igMultiPassStateAttr_GetVTable(void) {
    struct O_135270 o;
    igObject_InitHeader(&o.vt);
    o.vt = g_igMultiPassStateAttr_vtable;
    return *(int *)((char *)&o.vt + *(int *)(g_objectSystem[0] + 916));
}

void FUN_001352b0(void)
{
    igMetaObject_RunStaticInit(igMultiPassStateAttr_Register);
}

void igMultiPassStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMultiPassStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igMultiPassStateAttr_GetMetaObject,
        "igMultiPassStateAttr",
        0x10, /* instance size */
        igMultiPassStateAttr_GetVTable,
        &igMultiPassStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMultiPassStateAttr_GetMetaObject(void) {
    igMultiPassStateAttr_GetMetaObject();
}

static FieldFactory g_igMultiPassStateAttr_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_igMultiPassStateAttr_fieldTable[] = {
    "_numPasses",
};
static igMetaField **g_igMultiPassStateAttr_fieldHandles[] = {
    &g_igMultiPassStateAttr_numPassesMetaField,
};
static int g_igMultiPassStateAttr_fieldOffsets[] = {
    12,
};

void igMultiPassStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igMultiPassStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igMultiPassStateAttr_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_igMultiPassStateAttr_fieldTable, g_igMultiPassStateAttr_fieldHandles, g_igMultiPassStateAttr_fieldOffsets, temp_s1);
}

