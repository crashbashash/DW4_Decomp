void FUN_001384a0(int arg0) {
    FUN_00138570();
    igMetaObject_CreateInstance(*(int *)0x55F228, arg0);
}

igMetaObject *igDepthStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDepthStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138570();
    return g_igDepthStateAttr_metaObject[0];
}

int igDepthStateAttr_GetVTable(void) {
    struct Obj obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523cb0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00138570(void)
{
    igMetaObject_RunStaticInit(igDepthStateAttr_Register);
}

void igDepthStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDepthStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igDepthStateAttr_GetMetaObject,
        igDepthStateAttr_className,
        0x10, /* instance size */
        igDepthStateAttr_GetVTable,
        &igDepthStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDepthStateAttr_GetMetaObject(void) {
    igDepthStateAttr_GetMetaObject();
}

void igDepthStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igDepthStateAttr_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igDepthStateAttr_ctorTable[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &g_igDepthStateAttr_fieldTable[0], &DAT_00486758[0], &DAT_00486760[0], temp_s1);
}

