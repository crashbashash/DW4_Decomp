igMetaObject *g_igBitmapFont_metaObject;
igMetaField *g_igBitmapFont_charMetricsListMetaField;
igMetaField *g_igBitmapFont_textureBindMetaField;

igMetaObject *FUN_004524f0(void) {
    if (g_igBitmapFont_metaObject == 0) {
        g_igBitmapFont_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBitmapFont_metaObject;
}

igMetaObject *igBitmapFont_GetMetaObject(void)
{
    igMetaObject *g = g_igBitmapFont_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBitmapFont_RunStaticInit();
    return g_igBitmapFont_metaObject;
}

int igBitmapFont_GetVTable(void) {
    struct Obj_452590 obj;
    int t;
    igObject_InitHeader((igObject *)&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.vt = &g_igBitmapFont_vtable[0];
    obj.w7 = 0;
    obj.w8 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    obj.vt = &g_igBitmapFont_vtable[0];
    FUN_0019aa10(&obj.w8, -1);
    igSmartPointer_igCharMetricsList_Destruct(&obj.w7, -1);
    igFont_Destroy((igFont *)&obj, 0);
    return t;
}

void igBitmapFont_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igBitmapFont_Register);
}

static igMetaObjectCallback g_igBitmapFont_callbackList[] = { igCharMetricsList_RunStaticInit, igTextureBindAttr_EnsureRegistered, 0 };

CallbackArray *igBitmapFont_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBitmapFont_metaObject,
        igFont_Register,
        igFont_GetPublishedMetaObject,
        thunk_igBitmapFont_GetMetaObject,
        "igBitmapFont",
        0x24, /* instance size */
        igBitmapFont_GetVTable,
        &igBitmapFont_InitFields,
        0, /* extra callback item */
        g_igBitmapFont_callbackList /* callback list */
    );
}

void thunk_igBitmapFont_GetMetaObject(void) {
    igBitmapFont_GetMetaObject();
}

igMetaObject *FUN_004526c0(void) {
    return g_igFont_metaObject;
}

static FieldFactory g_igBitmapFont_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_igBitmapFont_fieldTable[] = {
    "_charMetricsList",
    "_textureBind",
};
static igMetaField **g_igBitmapFont_fieldHandles[] = {
    &g_igBitmapFont_charMetricsListMetaField,
    &g_igBitmapFont_textureBindMetaField,
};
static int g_igBitmapFont_fieldOffsets[] = {
    28,
    32,
};

void igBitmapFont_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igBitmapFont_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igBitmapFont_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00452790();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00132850();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igBitmapFont_fieldTable, g_igBitmapFont_fieldHandles, g_igBitmapFont_fieldOffsets, temp_s2);
}

