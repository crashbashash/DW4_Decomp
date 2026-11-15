igMetaObject *g_igBoundingBoxRenderer_metaObject;
igMetaField *g_igBoundingBoxRenderer_parametersMetaField;
igMetaField *g_igBoundingBoxRenderer_displayListMetaField;
igMetaField *g_igBoundingBoxRenderer_attrListMetaField;
igMetaField *g_igBoundingBoxRenderer_modelViewAttrMetaField;
igMetaField *g_igBoundingBoxRenderer_boxMetaField;
igMetaField *g_igBoundingBoxRenderer_borderMetaField;
igMetaField *g_igBoundingBoxRenderer_pathMetaField;
igMetaField *g_igBoundingBoxRenderer_drawMetaField;

igMetaObject *FUN_0045de90(void) {
    if (g_igBoundingBoxRenderer_metaObject == 0) {
        g_igBoundingBoxRenderer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igBoundingBoxRenderer_metaObject;
}

igMetaObject *igBoundingBoxRenderer_GetMetaObject(void)
{
    igMetaObject *g = ((igMetaObject *)g_igBoundingBoxRenderer_metaObject);
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_0045e050();
    return ((igMetaObject *)g_igBoundingBoxRenderer_metaObject);
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
    t = *(int *)((char *)&obj + *(int *)((char *)(((void *)g_objectSystem[0])) + 916));
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

static igMetaObjectCallback g_igBoundingBoxRenderer_callbackList[] = { FUN_0045b590, FUN_00138160, FUN_0013afe0, FUN_001357e0, FUN_001378f0, FUN_0019f7a0, 0 };

void igBoundingBoxRenderer_Register(void) {
    ViewerLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBoundingBoxRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igBoundingBoxRenderer_GetMetaObject,
        "igBoundingBoxRenderer",
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

static FieldFactory g_igBoundingBoxRenderer_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_igBoundingBoxRenderer_fieldTable[] = {
    "_parameters",
    "_displayList",
    "_attrList",
    "_modelViewAttr",
    "_box",
    "_border",
    "_path",
    "_draw",
};
static igMetaField **g_igBoundingBoxRenderer_fieldHandles[] = {
    &g_igBoundingBoxRenderer_parametersMetaField,
    &g_igBoundingBoxRenderer_displayListMetaField,
    &g_igBoundingBoxRenderer_attrListMetaField,
    &g_igBoundingBoxRenderer_modelViewAttrMetaField,
    &g_igBoundingBoxRenderer_boxMetaField,
    &g_igBoundingBoxRenderer_borderMetaField,
    &g_igBoundingBoxRenderer_pathMetaField,
    &g_igBoundingBoxRenderer_drawMetaField,
};
static int g_igBoundingBoxRenderer_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

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

    temp_s1 = g_igBoundingBoxRenderer_metaObject;
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, g_igBoundingBoxRenderer_ctorTable, 8);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_0045b420();
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
    igMetaObject_NameFields(temp_s1, g_igBoundingBoxRenderer_fieldTable, g_igBoundingBoxRenderer_fieldHandles, g_igBoundingBoxRenderer_fieldOffsets, temp_s0);
}

