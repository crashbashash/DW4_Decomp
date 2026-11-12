void FUN_001359a0(int arg0) {
    FUN_00135ac0();
    igMetaObject_CreateInstance(*(int *)0x55F000, arg0);
}

igMetaObject *FUN_001359e0(void) {
    if (g_igMatrixOptStateAttr_metaObject[0] == 0) {
        g_igMatrixOptStateAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igMatrixOptStateAttr_metaObject[0];
}

igMetaObject *igMatrixOptStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixOptStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135ac0();
    return g_igMatrixOptStateAttr_metaObject[0];
}

int igMatrixOptStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005234b0[0];
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
        g_igMatrixOptStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igMatrixOptStateAttr_GetMetaObject,
        igMatrixOptStateAttr_className,
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

void igMatrixOptStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igMatrixOptStateAttr_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486248[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486250[0], &DAT_00486258[0], &DAT_00486260[0], temp_s1);
}

