void FUN_00134690(int arg0) {
    FUN_001347c0();
    igMetaObject_CreateInstance(*(int *)0x55EF50, arg0);
}

igMetaObject *FUN_001346d0(void) {
    if (g_igProjectionMatrixAttr_metaObject[0] == 0) {
        g_igProjectionMatrixAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igProjectionMatrixAttr_metaObject[0];
}

igMetaObject *igProjectionMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igProjectionMatrixAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001347c0();
    return g_igProjectionMatrixAttr_metaObject[0];
}

int igProjectionMatrixAttr_GetVTable(void) {
    struct Obj_134770 o;
    igObject_InitHeader(&o);
    o.vt = &DAT_005230e0[0];
    igMatrix44f_SetIdentity(&o.pad[8]);
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001347c0(void)
{
    igMetaObject_RunStaticInit(igProjectionMatrixAttr_Register);
}

void igProjectionMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igProjectionMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igProjectionMatrixAttr_GetMetaObject,
        igProjectionMatrixAttr_className,
        0x4C, /* instance size */
        igProjectionMatrixAttr_GetVTable,
        &igProjectionMatrixAttr_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igProjectionMatrixAttr_GetMetaObject(void) {
    igProjectionMatrixAttr_GetMetaObject();
}

void igProjectionMatrixAttr_InitFields(void) {
    int temp_s2;
    int temp_s1;
    void *temp_s0;
    struct M o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    temp_s0 = (void *)g_igProjectionMatrixAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igProjectionMatrixAttr_ctorTable[0], 1);
    temp_s1 = (int)igMetaObject_GetFieldAt(temp_s0, temp_s2);
    o5.x = 0;
    o5.y = 0;
    o5.z = 0;
    o5.w = 0x3F800000;
    o4.x = 0;
    o4.y = 0;
    o4.z = 0x3F800000;
    o4.w = 0;
    o3.x = 0;
    o3.y = 0x3F800000;
    o3.z = 0;
    o3.w = 0;
    o2.x = 0x3F800000;
    o2.y = 0;
    o2.z = 0;
    o2.w = 0;
    FUN_00130e90(&o1, &o2, &o3, &o4, &o5);
    FUN_0018c640(temp_s1, &o1);
    igMetaObject_NameFields(temp_s0, &g_igProjectionMatrixAttr_fieldTable[0], &DAT_004860f0[0], &DAT_004860f8[0], temp_s2);
}

