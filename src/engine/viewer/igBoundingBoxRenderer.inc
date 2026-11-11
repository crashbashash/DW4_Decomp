int FUN_0045de90(void) {
    if (DAT_0058ce18[0] == 0) {
        DAT_0058ce18[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058ce18[0];
}

igMetaObject *igBoundingBoxRenderer_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject *)DAT_0058ce18[0]);
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0045e050();
    return ((igMetaObject *)DAT_0058ce18[0]);
}

int igBoundingBoxRenderer_GetVTable(void) {
    struct Obj_45df30 obj;
    int t;
    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00542a70[0];
    obj.w3 = 0;
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.w7 = 0;
    obj.w8 = 0;
    obj.w9 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)DAT_00586dc8[0])) + 916));
    obj.vt = &DAT_00542a70[0];
    FUN_001d6560(&obj.w9, -1);
    FUN_001353b0(&obj.w8, -1);
    FUN_001353b0(&obj.w7, -1);
    FUN_00142d10(&obj.w6, -1);
    FUN_0013bfe0(&obj.w5, -1);
    FUN_00197160(&obj.w4, -1);
    FUN_00459860((ObjectRefWord *)&obj.w3, -1);
    FUN_00230f70(&obj, 0);
    return t;
}

void FUN_0045e050(void)
{
    igMetaObject_RunStaticInit(igBoundingBoxRenderer_Register);
}

void igBoundingBoxRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoundingBoxRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igBoundingBoxRenderer_GetMetaObject,
        igBoundingBoxRenderer_className,
        0x2C, /* instance size */
        igBoundingBoxRenderer_GetVTable,
        &igBoundingBoxRenderer_InitFields,
        0, /* extra callback item */
        g_igBoundingBoxRenderer_callbackList /* callback list */
    );
}

void thunk_igBoundingBoxRenderer_GetMetaObject(void) {
    igBoundingBoxRenderer_GetMetaObject();
}

void igBoundingBoxRenderer_InitFields(void) {
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)DAT_0058ce18[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004d1940[0], 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = FUN_0045b420();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = FUN_00137fb0();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = FUN_0013af00();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_001356f0();
    ((igRefMetaField *)temp_s2_4)->_construct = 1;
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = FUN_00137850();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 5));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = FUN_00137850();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 6));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_0019f670();
    igMetaObject_NameFields(temp_s1, &DAT_004d1960[0], &DAT_004d1980[0], &DAT_004d19a0[0], temp_s0);
}

