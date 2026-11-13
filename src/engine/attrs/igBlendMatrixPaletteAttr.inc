void FUN_00139990(int arg0) {
    FUN_00139ab0();
    igMetaObject_CreateInstance(*(int *)0x55F360, arg0);
}

igMetaObject *FUN_001399d0(void) {
    if (g_igBlendMatrixPaletteAttr_metaObject[0] == 0) {
        g_igBlendMatrixPaletteAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igBlendMatrixPaletteAttr_metaObject[0];
}

igMetaObject *igBlendMatrixPaletteAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatrixPaletteAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139ab0();
    return g_igBlendMatrixPaletteAttr_metaObject[0];
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
        g_igBlendMatrixPaletteAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igBlendMatrixPaletteAttr_GetMetaObject,
        igBlendMatrixPaletteAttr_className,
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

void igBlendMatrixPaletteAttr_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBlendMatrixPaletteAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igBlendMatrixPaletteAttr_ctorTable[0], 4);
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
    igMetaObject_NameFields(temp_s0, &g_igBlendMatrixPaletteAttr_fieldTable[0], &DAT_00486a30[0], &DAT_00486a40[0], temp_s2);
}

