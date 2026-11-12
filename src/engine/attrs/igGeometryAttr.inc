void FUN_00137810(int arg0) {
    FUN_001378f0();
    igMetaObject_CreateInstance(*(int *)0x55F170, arg0);
}

igMetaObject *FUN_00137850(void) {
    if (g_igGeometryAttr_metaObject[0] == 0) {
        g_igGeometryAttr_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGeometryAttr_metaObject[0];
}

igMetaObject *igGeometryAttr_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttr_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001378f0();
    return g_igGeometryAttr_metaObject[0];
}

void FUN_001378f0(void)
{
    igMetaObject_RunStaticInit(igGeometryAttr_Register);
}

void igGeometryAttr_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igGeometryAttr_metaObject,
        igVisualAttribute_Register,
        igVisualAttribute_GetPublishedMetaObject,
        thunk_igGeometryAttr_GetMetaObject,
        igGeometryAttr_className,
        0x30, /* instance size */
        0,
        &igGeometryAttr_InitFields,
        0, /* extra callback item */
        g_igGeometryAttr_callbackList /* callback list */
    );
}

void thunk_igGeometryAttr_GetMetaObject(void) {
    igGeometryAttr_GetMetaObject();
}

void igGeometryAttr_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_v0;
    void *temp_s1;

    temp_s1 = (void *)(g_igGeometryAttr_metaObject[0]);
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004865a0[0], 9);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0014b980();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0014d7f0();
    temp_v0 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    FUN_002dc7a0(temp_v0, &DAT_00486658[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&FUN_00149aa0);
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_002ca450();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_0018a0a0();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_0018a0a0();
    igMetaObject_NameFields(temp_s1, &DAT_004865d0[0], &DAT_00486600[0], &DAT_00486630[0], temp_s0);
    *(int *)((char *)(g_igGeometryAttr_metaObject[0]) + 60) = (int)thunk_igGeometryAttr1_5_GetMetaObject;
}

