igMetaObject *g_igBlendMatrixPaletteAttr_metaObject;
igMetaField *g_igBlendMatrixPaletteAttr_matrixCacheMetaField;
igMetaField *g_igBlendMatrixPaletteAttr_matrixIndicesMetaField;
igMetaField *g_igBlendMatrixPaletteAttr_currentMatrixCountMetaField;
igMetaField *g_igBlendMatrixPaletteAttr_capacityMetaField;

void FUN_00139990(int arg0) {
    FUN_00139ab0();
    igMetaObject_CreateInstance(*(int *)0x55F360, arg0);
}

igMetaObject *FUN_001399d0(void) {
    if (g_igBlendMatrixPaletteAttr_metaObject == 0) {
        g_igBlendMatrixPaletteAttr_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igBlendMatrixPaletteAttr_metaObject;
}

igMetaObject *igBlendMatrixPaletteAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixPaletteAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139ab0();
    return g_igBlendMatrixPaletteAttr_metaObject;
}

int igBlendMatrixPaletteAttr_GetVTable(void) {
    union U_139a70 u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00524110[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00139ab0(void)
{
    igMetaObject_RunStaticInit(igBlendMatrixPaletteAttr_Register);
}

void igBlendMatrixPaletteAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatrixPaletteAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendMatrixPaletteAttr_GetMetaObject,
        "igBlendMatrixPaletteAttr",
        0x1C, /* instance size */
        igBlendMatrixPaletteAttr_GetVTable,
        &igBlendMatrixPaletteAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBlendMatrixPaletteAttr_GetMetaObject(void) {
    igBlendMatrixPaletteAttr_GetMetaObject();
}

static FieldFactory g_igBlendMatrixPaletteAttr_ctorTable[] = {
    igMemoryRefMetaField_Create,
    igMemoryRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igUnsignedIntMetaField_Create,
};
static const char *g_igBlendMatrixPaletteAttr_fieldTable[] = {
    "_matrixCache",
    "_matrixIndices",
    "_currentMatrixCount",
    "_capacity",
};
static igMetaField **g_igBlendMatrixPaletteAttr_fieldHandles[] = {
    &g_igBlendMatrixPaletteAttr_matrixCacheMetaField,
    &g_igBlendMatrixPaletteAttr_matrixIndicesMetaField,
    &g_igBlendMatrixPaletteAttr_currentMatrixCountMetaField,
    &g_igBlendMatrixPaletteAttr_capacityMetaField,
};
static int g_igBlendMatrixPaletteAttr_fieldOffsets[] = {
    12,
    16,
    20,
    24,
};

void igBlendMatrixPaletteAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igBlendMatrixPaletteAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igBlendMatrixPaletteAttr_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_001888e0();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igMemoryRefMetaField *)temp_s1_2)->_memType = igUnsignedIntMetaField_GetDefaultDescriptor();
    ((igRefMetaField *)temp_s1_2)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1_2)->_releaseOnReset = 1;
    igMetaObject_NameFields(temp_s0, g_igBlendMatrixPaletteAttr_fieldTable, g_igBlendMatrixPaletteAttr_fieldHandles, g_igBlendMatrixPaletteAttr_fieldOffsets, temp_s2);
}

