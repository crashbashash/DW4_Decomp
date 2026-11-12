void FUN_00138cb0(int arg0) {
    FUN_00138d80();
    igMetaObject_CreateInstance(*(int *)0x55F2B0, arg0);
}

igMetaObject *igColorMaskAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igColorMaskAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138d80();
    return g_igColorMaskAttr_metaObject[0];
}

int igColorMaskAttr_GetVTable(void) {
    struct Obj_138d40 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523e50[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00138d80(void)
{
    igMetaObject_RunStaticInit(igColorMaskAttr_Register);
}

void igColorMaskAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igColorMaskAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igColorMaskAttr_GetMetaObject,
        igColorMaskAttr_className,
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

void igColorMaskAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f2b0[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004868a0[0], 5);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3), 1);
    igMetaObject_NameFields(temp_s0, &DAT_004868c0[0], &DAT_004868e0[0], &DAT_00486900[0], temp_s1);
}

