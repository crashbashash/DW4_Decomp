igMetaObject *FUN_0045d830(void) {
    if (g_igNormalsRenderer_metaObject[0] == 0) {
        g_igNormalsRenderer_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igNormalsRenderer_metaObject[0];
}

void *igNormalsRenderer_GetMetaObject(void) {
    igMetaObject *g = g_igNormalsRenderer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0045d9f0();
    }
    return g_igNormalsRenderer_metaObject[0];
}

int igNormalsRenderer_GetVTable(void) {
    struct Obj_45d8d0 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_005422a0[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w10 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
    obj.vt = &DAT_005422a0[0];
    FUN_001d6560(&obj.w10, -1);
    FUN_00136e10(&obj.w8, -1);
    FUN_0019ab10(&obj.w7, -1);
    FUN_00142d10(&obj.w6, -1);
    FUN_0013bfe0(&obj.w5, -1);
    FUN_0013bfe0(&obj.w4, -1);
    FUN_00459860((ObjectRefWord *)&obj.w3, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void FUN_0045d9f0(void)
{
    igMetaObject_RunStaticInit(igNormalsRenderer_Register);
}

void igNormalsRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNormalsRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igNormalsRenderer_GetMetaObject,
        igNormalsRenderer_className,
        0x30, /* instance size */
        igNormalsRenderer_GetVTable,
        &igNormalsRenderer_InitFields,
        0, /* extra callback item */
        g_igNormalsRenderer_callbackList /* callback list */
    );
}

void thunk_igNormalsRenderer_GetMetaObject(void) {
    igNormalsRenderer_GetMetaObject();
}

void igNormalsRenderer_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;

    temp_s1 = (void *)g_igNormalsRenderer_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &g_igNormalsRenderer_ctorTable[0], 9);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_001356f0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00138f20();
    ((igRefMetaField *)temp_s2_5)->_construct = 1;
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_0013a4d0();
    ((igRefMetaField *)temp_s2_6)->_construct = 1;
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s1, &g_igNormalsRenderer_fieldTable[0], &DAT_004d1870[0], &DAT_004d18a0[0], temp_s0);
}

