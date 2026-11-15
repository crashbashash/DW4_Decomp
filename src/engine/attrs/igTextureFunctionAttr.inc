igMetaObject *g_igTextureFunctionAttr_metaObject;
igMetaField *g_igTextureFunctionAttr_modeMetaField;
igMetaField *g_igTextureFunctionAttr_unitIDMetaField;
igMetaField *g_igTextureFunctionAttr_arg0MetaField;
igMetaField *g_igTextureFunctionAttr_arg1MetaField;
igMetaField *g_igTextureFunctionAttr_typeMetaField;
igMetaField *g_igTextureFunctionAttr_call_stateMetaField;
igMetaField *g_igTextureFunctionAttr_functionTypeMetaField;

void FUN_00131c60(int arg0) {
    FUN_00131d80();
    igMetaObject_CreateInstance(*(int *)0x55ED00, arg0);
}

igMetaObject *FUN_00131ca0(void) {
    if (g_igTextureFunctionAttr_metaObject == 0) {
        g_igTextureFunctionAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igTextureFunctionAttr_metaObject;
}

igMetaObject *igTextureFunctionAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureFunctionAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00131d80();
    return g_igTextureFunctionAttr_metaObject;
}

int igTextureFunctionAttr_GetVTable(void) {
    struct Obj_131d40 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00522a10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00131d80(void)
{
    igMetaObject_RunStaticInit(igTextureFunctionAttr_Register);
}

void igTextureFunctionAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureFunctionAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igTextureFunctionAttr_GetMetaObject,
        "igTextureFunctionAttr",
        sizeof(igTextureFunctionAttr),                     /* Instance size. */
        igTextureFunctionAttr_GetVTable,
        &igTextureFunctionAttr_InitFields,
        FUN_00131f70, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTextureFunctionAttr_GetMetaObject(void) {
    igTextureFunctionAttr_GetMetaObject();
}

static FieldFactory g_igTextureFunctionAttr_ctorTable[] = {
    igEnumMetaField_Create,
    igIntMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igEnumMetaField_Create,
    igUnsignedCharMetaField_Create,
    igEnumMetaField_Create,
};
static const char *g_igTextureFunctionAttr_fieldTable[] = {
    "_mode",
    "_unitID",
    "_arg0",
    "_arg1",
    "_type",
    "_call_state",
    "_functionType",
};
static igMetaField **g_igTextureFunctionAttr_fieldHandles[] = {
    &g_igTextureFunctionAttr_modeMetaField,
    &g_igTextureFunctionAttr_unitIDMetaField,
    &g_igTextureFunctionAttr_arg0MetaField,
    &g_igTextureFunctionAttr_arg1MetaField,
    &g_igTextureFunctionAttr_typeMetaField,
    &g_igTextureFunctionAttr_call_stateMetaField,
    &g_igTextureFunctionAttr_functionTypeMetaField,
};
static int g_igTextureFunctionAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
};

int g_igTextureFunctionAttr_modeDefault = 1;

void igTextureFunctionAttr_InitFields(void) {
    igMetaObject *temp_s1;
    int temp_s0;
    struct TextureMetaFieldView *temp_v0;
    struct TextureMetaFieldView *temp_v0_2;
    struct TextureMetaFieldView *t1;
    struct TextureMetaFieldView *t2;
    struct TextureMetaFieldView *t3;
    struct TextureMetaFieldView *t4;

    temp_s1 = g_igTextureFunctionAttr_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igTextureFunctionAttr_ctorTable, 7);
    temp_v0 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0);
    igEnumMetaField_SetDefaultValue(temp_v0, g_igTextureFunctionAttr_modeDefault);
    temp_v0->f52 = igMetaEnum_GetEmpty;
    t1 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1);
    t1->f48 = (void (*)())FUN_00141250;
    t2 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2);
    t2->f52 = FUN_0014d450;
    t3 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3);
    t3->f52 = FUN_0014d450;
    t4 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4);
    t4->f52 = FUN_0014d4b0;
    igUnsignedCharMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5), 2);
    temp_v0_2 = (TextureMetaFieldView *)igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6);
    igEnumMetaField_SetDefaultValue(temp_v0_2, 0);
    temp_v0_2->f52 = FUN_0014d510;
    igMetaObject_NameFields(temp_s1, g_igTextureFunctionAttr_fieldTable, g_igTextureFunctionAttr_fieldHandles, g_igTextureFunctionAttr_fieldOffsets, temp_s0);
}

void FUN_00131f70(void) {
    FUN_001412a0();
}

