igMetaObject *g_igColorMaskAttr_metaObject;
igMetaField *g_igColorMaskAttr_redMetaField;
igMetaField *g_igColorMaskAttr_greenMetaField;
igMetaField *g_igColorMaskAttr_blueMetaField;
igMetaField *g_igColorMaskAttr_alphaMetaField;
igMetaField *g_igColorMaskAttr_unusedMetaField;

void FUN_00138cb0(int arg0) {
    FUN_00138d80();
    igMetaObject_CreateInstance(*(int *)0x55F2B0, arg0);
}

igMetaObject *igColorMaskAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igColorMaskAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138d80();
    return g_igColorMaskAttr_metaObject;
}

int igColorMaskAttr_GetVTable(void) {
    struct Obj_138d40 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523e50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00138d80(void)
{
    igMetaObject_RunStaticInit(igColorMaskAttr_Register);
}

void igColorMaskAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igColorMaskAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igColorMaskAttr_GetMetaObject,
        "igColorMaskAttr",
        0x14, /* instance size */
        igColorMaskAttr_GetVTable,
        &igColorMaskAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igColorMaskAttr_GetMetaObject(void) {
    igColorMaskAttr_GetMetaObject();
}

static FieldFactory g_igColorMaskAttr_ctorTable[] = {
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igUnsignedIntMetaField_Create,
};
static const char *g_igColorMaskAttr_fieldTable[] = {
    "_red",
    "_green",
    "_blue",
    "_alpha",
    "_unused",
};
static igMetaField **g_igColorMaskAttr_fieldHandles[] = {
    &g_igColorMaskAttr_redMetaField,
    &g_igColorMaskAttr_greenMetaField,
    &g_igColorMaskAttr_blueMetaField,
    &g_igColorMaskAttr_alphaMetaField,
    &g_igColorMaskAttr_unusedMetaField,
};
static int g_igColorMaskAttr_fieldOffsets[] = {
    12,
    13,
    14,
    15,
    16,
};

void igColorMaskAttr_InitFields(void) {
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igColorMaskAttr_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igColorMaskAttr_ctorTable, 5);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 1);
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1);
    igMetaObject_NameFields(temp_s0, g_igColorMaskAttr_fieldTable, g_igColorMaskAttr_fieldHandles, g_igColorMaskAttr_fieldOffsets, temp_s1);
}

