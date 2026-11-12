void FUN_00139370(int arg0) {
    FUN_00139440();
    igMetaObject_CreateInstance(*(int *)0x55F308, arg0);
}

igMetaObject *igClearAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igClearAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00139440();
    return g_igClearAttr_metaObject[0];
}

int igClearAttr_GetVTable(void) {
    struct Obj_139400 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524000[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00139440(void)
{
    igMetaObject_RunStaticInit(igClearAttr_Register);
}

void igClearAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igClearAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igClearAttr_GetMetaObject,
        igClearAttr_className,
        0x48, /* instance size */
        igClearAttr_GetVTable,
        &igClearAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igClearAttr_GetMetaObject(void) {
    igClearAttr_GetMetaObject();
}

void igClearAttr_InitFields(void) {
    void *temp_v0_2;
    void *temp_v0;
    void *temp_a0_2;
    void *temp_a0;
    void *temp_s1;
    int temp_s0;
    struct V v1;
    struct V v2;

    temp_s1 = (void *)g_igClearAttr_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_00486960[0], 7);
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    v1.x = 0;
    v1.w = 0x3F800000;
    v1.y = 0;
    v1.z = 0;
    FUN_0018e670(temp_a0, &v1);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    v2.x = 0;
    v2.y = 0;
    v2.z = 0;
    v2.w = 0;
    FUN_0018e670(temp_a0_2, &v2);
    FUN_002d9500(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3), 0x3FF00000LL << 0x20);
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    FUN_0030e9b0(temp_v0, -1);
    *(char *)((char *)(temp_v0) + 38) = 0;
    temp_v0_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    FUN_002e3810(temp_v0_2, 1.0f);
    *(char *)((char *)(temp_v0_2) + 38) = 0;
    igMetaObject_NameFields(temp_s1, &DAT_00486980[0], &DAT_004869a0[0], &DAT_004869c0[0], temp_s0);
}

