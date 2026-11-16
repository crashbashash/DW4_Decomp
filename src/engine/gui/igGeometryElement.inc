igMetaObject *g_igGeometryElement_metaObject;
igMetaField *g_igGeometryElement_geometryMetaField;
igMetaField *g_igGeometryElement_defaultSizeMetaField;
igMetaField *g_igGeometryElement_colorMetaField;
igMetaField *g_igGeometryElement_sharableAttrsMetaField;

igMetaObject *FUN_004505b0(void) {
    if (g_igGeometryElement_metaObject == 0) {
        g_igGeometryElement_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGeometryElement_metaObject;
}

igMetaObject *igGeometryElement_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryElement_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGeometryElement_EnsureRegistered();
    return g_igGeometryElement_metaObject;
}

void igGeometryElement_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGeometryElement_Register);
}

static igMetaObjectCallback g_igGeometryElement_callbackList[] = { igGeometry_EnsureRegistered, igAttrList_EnsureRegistered, 0 };

void igGeometryElement_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igGeometryElement_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGeometryElement_GetMetaObject,
        "igGeometryElement",
        0x2C, /* instance size */
        0,
        &igGeometryElement_InitFields,
        0, /* extra callback item */
        g_igGeometryElement_callbackList /* callback list */
    );
}

void thunk_igGeometryElement_GetMetaObject(void) {
    igGeometryElement_GetMetaObject();
}

static FieldFactory g_igGeometryElement_ctorTable[] = {
    igObjectRefMetaField_Create,
    FUN_00187890,
    FUN_001872a0,
    igObjectRefMetaField_Create,
};
static const char *g_igGeometryElement_fieldTable[] = {
    "_geometry",
    "_defaultSize",
    "_color",
    "_sharableAttrs",
};
static igMetaField **g_igGeometryElement_fieldHandles[] = {
    &g_igGeometryElement_geometryMetaField,
    &g_igGeometryElement_defaultSizeMetaField,
    &g_igGeometryElement_colorMetaField,
    &g_igGeometryElement_sharableAttrsMetaField,
};
static int g_igGeometryElement_fieldOffsets[] = {
    8,
    12,
    24,
    40,
};

void igGeometryElement_InitFields(void) {
    struct GeometryMetaFieldView { char p[52]; char f52; char p2[3]; int f56; };
    void *temp_a0;
    struct GeometryMetaFieldView *temp_s1_2;
    int temp_s2;
    struct GeometryMetaFieldView *temp_s1;
    void *temp_s0;
    void *temp_a0_2;
    float v4[4];
    float v3[3];

    temp_s0 = (void *)g_igGeometryElement_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igGeometryElement_ctorTable, 4);
    temp_s1 = (struct GeometryMetaFieldView *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    temp_s1->f56 = igGeometry_GetOrCreateMetaObject();
    temp_s1->f52 = 1;
    temp_a0 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    v3[0] = 0.0f;
    v3[1] = 0.0f;
    v3[2] = 0.0f;
    FUN_0018e470(temp_a0, v3);
    temp_a0_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    v4[0] = 1.0f;
    v4[1] = 1.0f;
    v4[2] = 1.0f;
    v4[3] = 1.0f;
    FUN_0018e670(temp_a0_2, v4);
    temp_s1_2 = (struct GeometryMetaFieldView *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 3));
    temp_s1_2->f56 = igAttrList_GetOrCreateMetaObject();
    temp_s1_2->f52 = 1;
    igMetaObject_NameFields(temp_s0, g_igGeometryElement_fieldTable, g_igGeometryElement_fieldHandles, g_igGeometryElement_fieldOffsets, temp_s2);
}

