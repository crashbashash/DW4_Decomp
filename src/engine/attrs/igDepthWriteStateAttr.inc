int FUN_001382a0(void) {
    if (DAT_0055f218[0] == 0) {
        DAT_0055f218[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f218[0];
}

igMetaObject *igDepthWriteStateAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igDepthWriteStateAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00138380();
    return g_igDepthWriteStateAttr_metaObject[0];
}

int igDepthWriteStateAttr_GetVTable(void) {
    struct Obj_138340 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523c20[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_00138380(void)
{
    igMetaObject_RunStaticInit(igDepthWriteStateAttr_Register);
}

void igDepthWriteStateAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDepthWriteStateAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igDepthWriteStateAttr_GetMetaObject,
        igDepthWriteStateAttr_className,
        0x10, /* instance size */
        igDepthWriteStateAttr_GetVTable,
        &igDepthWriteStateAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDepthWriteStateAttr_GetMetaObject(void) {
    igDepthWriteStateAttr_GetMetaObject();
}

void igDepthWriteStateAttr_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0055f218[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00486728[0], 1);
    FUN_002d3890(igMetaObject_GetFieldAt(temp_s0, temp_s1), 1);
    igMetaObject_NameFields(temp_s0, &DAT_00486730[0], &DAT_00486738[0], &DAT_00486740[0], temp_s1);
}

