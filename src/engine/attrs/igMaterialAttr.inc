igMetaObject *igMaterialAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igMaterialAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00135c70();
    return g_igMaterialAttr_metaObject[0];
}

int igMaterialAttr_GetVTable(void) {
    struct Obj_135c30 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523540[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00135c70(void)
{
    igMetaObject_RunStaticInit(igMaterialAttr_Register);
}

void igMaterialAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMaterialAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igMaterialAttr_GetMetaObject,
        igMaterialAttr_className,
        0x54, /* instance size */
        igMaterialAttr_GetVTable,
        &igMaterialAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMaterialAttr_GetMetaObject(void) {
    igMaterialAttr_GetMetaObject();
}

void igMaterialAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;
    int temp_a0_4;
    int temp_a0_3;
    int temp_a0_2;
    int temp_a0;
    struct V v1;
    struct V v2;
    struct V v3;
    struct V v4;

    temp_s0 = (void *)g_igMaterialAttr_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igMaterialAttr_ctorTable[0], 6);
    temp_a0 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 1);
    v1.x = 0;
    v1.w = 0x3F800000;
    v1.y = 0;
    v1.z = 0;
    FUN_0018e670(temp_a0, &v1);
    temp_a0_2 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 2);
    v2.x = 0;
    v2.w = 0x3F800000;
    v2.y = 0;
    v2.z = 0;
    FUN_0018e670(temp_a0_2, &v2);
    temp_a0_3 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 3);
    v3.x = 0;
    v3.w = 0x3F800000;
    v3.y = 0;
    v3.z = 0;
    FUN_0018e670(temp_a0_3, &v3);
    temp_a0_4 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s1 + 4);
    v4.x = 0;
    v4.w = 0x3F800000;
    v4.y = 0;
    v4.z = 0;
    FUN_0018e670(temp_a0_4, &v4);
    igMetaObject_NameFields(temp_s0, &g_igMaterialAttr_fieldTable[0], &DAT_004862b0[0], &DAT_004862d0[0], temp_s1);
}

