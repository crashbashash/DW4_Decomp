igMetaObject *igVertexBlendStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igVertexBlendStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00130830();
    return g_igVertexBlendStateAttr_metaObject[0];
}

int igVertexBlendStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005225b0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00130830(void)
{
    igMetaObject_RunStaticInit(igVertexBlendStateAttr_Register);
}

void igVertexBlendStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexBlendStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igVertexBlendStateAttr_GetMetaObject,
        igVertexBlendStateAttr_className,
        0x10, /* instance size */
        igVertexBlendStateAttr_GetVTable,
        &igVertexBlendStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igVertexBlendStateAttr_GetMetaObject(void) {
    igVertexBlendStateAttr_GetMetaObject();
}

void igVertexBlendStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055ec18[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004859c0[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004859c8[0], &DAT_004859d0[0], &DAT_004859d8[0], temp_s1);
}

