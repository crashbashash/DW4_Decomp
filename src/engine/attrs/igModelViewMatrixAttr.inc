int FUN_001356b0(int arg0) {
    FUN_001357e0();
    return igMetaObject_CreateInstance(*(int *)0x55EFE8, arg0);
}

igMetaObject *FUN_001356f0(void) {
    if (g_igModelViewMatrixAttr_metaObject[0] == 0) {
        g_igModelViewMatrixAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igModelViewMatrixAttr_metaObject[0];
}

igMetaObject *igModelViewMatrixAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igModelViewMatrixAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001357e0();
    return g_igModelViewMatrixAttr_metaObject[0];
}

int igModelViewMatrixAttr_GetVTable(void) {
    struct Obj_135790 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00523420[0];
    igMatrix44f_SetIdentity(&obj.pad[8]);
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001357e0(void)
{
    igMetaObject_RunStaticInit(igModelViewMatrixAttr_Register);
}

void igModelViewMatrixAttr_Register(void) {
    AttrsLibrary_MarkRegistered();  /* Set-once latch run before every registration of this family. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igModelViewMatrixAttr_GetMetaObject,
        igModelViewMatrixAttr_className,
        0x4C,                                              /* instance size (the reflected struct is shorter: igMatrix44f is reflected as one int) */
        igModelViewMatrixAttr_GetVTable,
        &igModelViewMatrixAttr_InitFields,
        FUN_00135980,                                      /* static-initializer callback item (appended on fresh configuration) */
        0                                                  /* 0-terminated dependency-callback list */
    );
}

void thunk_igModelViewMatrixAttr_GetMetaObject(void) {
    igModelViewMatrixAttr_GetMetaObject();
}

void igModelViewMatrixAttr_InitFields(void) {
    int temp_s2;
    int temp_s1;
    void *temp_s0;
    struct M o1;
    struct V o2;
    struct V o3;
    struct V o4;
    struct V o5;

    temp_s0 = (void *)g_igModelViewMatrixAttr_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igModelViewMatrixAttr_ctorTable[0], 1);
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
    igMetaObject_NameFields(temp_s0, &g_igModelViewMatrixAttr_fieldTable[0], &DAT_00486238[0], &DAT_00486240[0], temp_s2);
    igMetaObject_AddExitCallback(&thunk_FUN_0013f730);
}

void FUN_00135980(void) {
    FUN_0013f670();
}

void thunk_FUN_0013f730(void) {
    FUN_0013f730();
}

