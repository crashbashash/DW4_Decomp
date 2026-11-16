igMetaObject *g_igBlendMatricesAttr_metaObject;
igMetaField *g_igBlendMatricesAttr_matrixCacheMetaField;
igMetaField *g_igBlendMatricesAttr_currentMatrixCountMetaField;
igMetaField *g_igBlendMatricesAttr_matrixCacheCapacityMetaField;

void FUN_00139c10(int arg0) {
    FUN_00139ce0();
    igMetaObject_CreateInstance(*(int *)0x55F388, arg0);
}

igMetaObject *igBlendMatricesAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatricesAttr_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139ce0();
    return g_igBlendMatricesAttr_metaObject;
}

int igBlendMatricesAttr_GetVTable(void) {
    struct Obj_139ca0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igBlendMatricesAttr_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00139ce0(void)
{
    igMetaObject_RunStaticInit(igBlendMatricesAttr_Register);
}

void igBlendMatricesAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatricesAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendMatricesAttr_GetMetaObject,
        "igBlendMatricesAttr",
        0x18, /* instance size */
        igBlendMatricesAttr_GetVTable,
        &igBlendMatricesAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igBlendMatricesAttr_GetMetaObject(void) {
    igBlendMatricesAttr_GetMetaObject();
}

static FieldFactory g_igBlendMatricesAttr_ctorTable[] = {
    igMemoryRefMetaField_Create,
    igUnsignedIntMetaField_Create,
    igUnsignedIntMetaField_Create,
};
static const char *g_igBlendMatricesAttr_fieldTable[] = {
    "_matrixCache",
    "_currentMatrixCount",
    "_matrixCacheCapacity",
};
static igMetaField **g_igBlendMatricesAttr_fieldHandles[] = {
    &g_igBlendMatricesAttr_matrixCacheMetaField,
    &g_igBlendMatricesAttr_currentMatrixCountMetaField,
    &g_igBlendMatricesAttr_matrixCacheCapacityMetaField,
};
static int g_igBlendMatricesAttr_fieldOffsets[] = {
    12,
    16,
    20,
};

void igBlendMatricesAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igBlendMatricesAttr_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igBlendMatricesAttr_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_001888e0();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields(temp_s0, g_igBlendMatricesAttr_fieldTable, g_igBlendMatricesAttr_fieldHandles, g_igBlendMatricesAttr_fieldOffsets, temp_s2);
}

