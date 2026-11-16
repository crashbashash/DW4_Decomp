igMetaObject *g_igMatrixOptStateAttr_metaObject;
igMetaField *g_igMatrixOptStateAttr_enabledMetaField;

void FUN_001359a0(int arg0) {
    FUN_00135ac0();
    igMetaObject_CreateInstance(*(int *)0x55F000, arg0);
}

igMetaObject *FUN_001359e0(void) {
    if (g_igMatrixOptStateAttr_metaObject == 0) {
        g_igMatrixOptStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igMatrixOptStateAttr_metaObject;
}

igMetaObject *igMatrixOptStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixOptStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135ac0();
    return g_igMatrixOptStateAttr_metaObject;
}

int igMatrixOptStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &g_igMatrixOptStateAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00135ac0(void)
{
    igMetaObject_RunStaticInit(igMatrixOptStateAttr_Register);
}

void igMatrixOptStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMatrixOptStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igMatrixOptStateAttr_GetMetaObject,
        "igMatrixOptStateAttr",
        0x10, /* instance size */
        igMatrixOptStateAttr_GetVTable,
        &igMatrixOptStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMatrixOptStateAttr_GetMetaObject(void) {
    igMatrixOptStateAttr_GetMetaObject();
}

static FieldFactory g_igMatrixOptStateAttr_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_igMatrixOptStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igMatrixOptStateAttr_fieldHandles[] = {
    &g_igMatrixOptStateAttr_enabledMetaField,
};
static int g_igMatrixOptStateAttr_fieldOffsets[] = {
    12,
};

void igMatrixOptStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igMatrixOptStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igMatrixOptStateAttr_ctorTable, 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, g_igMatrixOptStateAttr_fieldTable, g_igMatrixOptStateAttr_fieldHandles, g_igMatrixOptStateAttr_fieldOffsets, temp_s1);
}

