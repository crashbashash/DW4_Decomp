igMetaObject *g_beLOA_metaObject;
igMetaField *g_beLOA_rangeMetaField;
igMetaField *g_beLOA_maxAlphaMetaField;
igMetaField *g_beLOA_addAlphaMetaField;
igMetaField *g_beLOA_oldTimeMetaField;
igMetaField *g_beLOA_statusMetaField;
igMetaField *g_beLOA_colorMetaField;
igMetaField *g_beLOA_overrideAttrListMetaField;
igMetaField *g_beLOA_blendStateAttrMetaField;
igMetaField *g_beLOA_blendFunctionAttrMetaField;
igMetaField *g_beLOA_colorAttrMetaField;

igMetaObject *beLOA_GetMetaObject(void)
{
    igMetaObject *g = g_beLOA_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beLOA_EnsureRegistered();
    return g_beLOA_metaObject;
}

int beLOA_GetVTable(void) {
    beLOA obj;
    int *blendFunctionAttrSlot;
    int *blendStateAttrSlot;
    int *overrideAttrListSlot;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._bound = 0;
    obj._parentList = 0;
    obj._childList = 0;
    obj._vtable = (int)&g_beLOA_vtable[0];
    overrideAttrListSlot = &obj._overrideAttrList;
    *overrideAttrListSlot = 0;
    blendStateAttrSlot = &obj._blendStateAttr;
    *blendStateAttrSlot = 0;
    blendFunctionAttrSlot = &obj._blendFunctionAttr;
    *blendFunctionAttrSlot = 0;
    obj._colorAttr = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beLOA_vtable[0];
    igSmartPointer_igColorAttr_Destruct(&obj._colorAttr, -1);
    igSmartPointer_igBlendFunctionAttr_Destruct(blendFunctionAttrSlot, -1);
    igSmartPointer_igBlendStateAttr_Destruct(blendStateAttrSlot, -1);
    igSmartPointer_igAttrList_Destruct(overrideAttrListSlot, -1);
    igGroup_Destroy(&obj, 0);
    return vtable;
}

void beLOA_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLOA_Register);
}

static igMetaObjectCallback g_beLOA_callbackList[] = { igAttrList_EnsureRegistered, igBlendStateAttr_EnsureRegistered, igBlendFunctionAttr_EnsureRegistered, igColorAttr_EnsureRegistered, 0 };

void *beLOA_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLOA_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        beLOA_GetMetaObjectFunction,
        "beLOA",
        0x60, /* instance size */
        beLOA_GetVTable,
        beLOA_InitFields,
        beLOA_StaticInitCallback, /* extra callback item */
        g_beLOA_callbackList /* callback list */
    );
}

void beLOA_GetMetaObjectFunction(void)
{
    beLOA_GetMetaObject();
}

static FieldFactory g_beLOA_ctorTable[] = {
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igFloatMetaField_Create,
    igLongMetaField_Create,
    igIntMetaField_Create,
    igVec4fMetaField_CreateInstance,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beLOA_fieldTable[] = {
    "_range",
    "_maxAlpha",
    "_addAlpha",
    "_oldTime",
    "_status",
    "_color",
    "_overrideAttrList",
    "_blendStateAttr",
    "_blendFunctionAttr",
    "_colorAttr",
};
static igMetaField **g_beLOA_fieldHandles[] = {
    &g_beLOA_rangeMetaField,
    &g_beLOA_maxAlphaMetaField,
    &g_beLOA_addAlphaMetaField,
    &g_beLOA_oldTimeMetaField,
    &g_beLOA_statusMetaField,
    &g_beLOA_colorMetaField,
    &g_beLOA_overrideAttrListMetaField,
    &g_beLOA_blendStateAttrMetaField,
    &g_beLOA_blendFunctionAttrMetaField,
    &g_beLOA_colorAttrMetaField,
};
static int g_beLOA_fieldOffsets[] = {
    32,
    36,
    40,
    48,
    56,
    60,
    76,
    80,
    84,
    88,
};

void beLOA_InitFields(void) {
    int colorDefault[4];
    int base;
    void *color;
    void *overrideAttrList;
    void *blendStateAttr;
    void *blendFunctionAttr;
    void *colorAttr;
    void *meta;

    meta = (void *)g_beLOA_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLOA_ctorTable, 0xA);
    color = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    colorDefault[0] = 0x3F800000;
    colorDefault[1] = 0x3F800000;
    colorDefault[2] = 0x3F800000;
    colorDefault[3] = 0x3F800000;
    igVec4fMetaField_SetDefault(color, colorDefault);
    overrideAttrList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)overrideAttrList)->_metaObject = igAttrList_GetOrCreateMetaObject();
    ((igRefMetaField *)overrideAttrList)->_construct = 1;
    blendStateAttr = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)blendStateAttr)->_metaObject = igBlendStateAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)blendStateAttr)->_construct = 1;
    blendFunctionAttr = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)blendFunctionAttr)->_metaObject = igBlendFunctionAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)blendFunctionAttr)->_construct = 1;
    colorAttr = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)colorAttr)->_metaObject = igColorAttr_GetOrCreateMetaObject();
    ((igRefMetaField *)colorAttr)->_construct = 1;
    igMetaObject_NameFields(meta, g_beLOA_fieldTable, g_beLOA_fieldHandles, g_beLOA_fieldOffsets, base);
}

void beLOA_StaticInitCallback(void)
{
    beLOA_RegisterTraversalFunction();
}

