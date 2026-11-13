igMetaObject *FUN_00134fb0(void) {
    if (g_igNormalizeNormalsStateAttr_metaObject[0] == 0) {
        g_igNormalizeNormalsStateAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igNormalizeNormalsStateAttr_metaObject[0];
}

igMetaObject *igNormalizeNormalsStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igNormalizeNormalsStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135090();
    return g_igNormalizeNormalsStateAttr_metaObject[0];
}

int igNormalizeNormalsStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523310[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00135090(void)
{
    igMetaObject_RunStaticInit(igNormalizeNormalsStateAttr_Register);
}

void igNormalizeNormalsStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNormalizeNormalsStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igNormalizeNormalsStateAttr_GetMetaObject,
        igNormalizeNormalsStateAttr_className,
        0x10, /* instance size */
        igNormalizeNormalsStateAttr_GetVTable,
        &igNormalizeNormalsStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igNormalizeNormalsStateAttr_GetMetaObject(void) {
    igNormalizeNormalsStateAttr_GetMetaObject();
}

void igNormalizeNormalsStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igNormalizeNormalsStateAttr_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igNormalizeNormalsStateAttr_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_igNormalizeNormalsStateAttr_fieldTable[0], &DAT_004861f0[0], &DAT_004861f8[0], temp_s1);
}

