igMetaObject *g_igAlphaStateAttr_metaObject;
igMetaField *g_igAlphaStateAttr_enabledMetaField;

void FUN_0013b270(int arg0) {
    FUN_0013b390();
    igMetaObject_CreateInstance(*(int *)0x55F480, arg0);
}

igMetaObject *FUN_0013b2b0(void) {
    if (g_igAlphaStateAttr_metaObject == 0) {
        g_igAlphaStateAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAlphaStateAttr_metaObject;
}

igMetaObject *igAlphaStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igAlphaStateAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013b390();
    return g_igAlphaStateAttr_metaObject;
}

int igAlphaStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524300[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0013b390(void)
{
    igMetaObject_RunStaticInit(igAlphaStateAttr_Register);
}

void igAlphaStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAlphaStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igAlphaStateAttr_GetMetaObject,
        "igAlphaStateAttr",
        0x10, /* instance size */
        igAlphaStateAttr_GetVTable,
        &igAlphaStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAlphaStateAttr_GetMetaObject(void) {
    igAlphaStateAttr_GetMetaObject();
}

static FieldFactory g_igAlphaStateAttr_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_igAlphaStateAttr_fieldTable[] = {
    "_enabled",
};
static igMetaField **g_igAlphaStateAttr_fieldHandles[] = {
    &g_igAlphaStateAttr_enabledMetaField,
};
static int g_igAlphaStateAttr_fieldOffsets[] = {
    12,
};

void igAlphaStateAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igAlphaStateAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igAlphaStateAttr_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_igAlphaStateAttr_fieldTable, g_igAlphaStateAttr_fieldHandles, g_igAlphaStateAttr_fieldOffsets, temp_s1);
}

