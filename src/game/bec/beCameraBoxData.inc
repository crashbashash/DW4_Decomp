igMetaObject *g_beCameraBoxData_metaObject;
igMetaField *g_beCameraBoxData_switchMetaField;
igMetaField *g_beCameraBoxData_geometryListMetaField;
igMetaField *g_beCameraBoxData_transformListMetaField;
igMetaField *g_beCameraBoxData_eyePosListMetaField;
igMetaField *g_beCameraBoxData_intPosListMetaField;

void *beCameraBoxData_GetMetaObject(void) {
    igMetaObject *g = g_beCameraBoxData_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beCameraBoxData_EnsureRegistered();
    }
    return g_beCameraBoxData_metaObject;
}

int beCameraBoxData_GetVTable(void) {
    struct Obj_369200 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.vt = &g_beCameraBoxData_vtable[0];
    obj.w[1] = 0;
    obj.w[2] = 0;
    obj.w[3] = 0;
    obj.w[4] = 0;
    obj.w[5] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beCameraBoxData_vtable[0];
    FUN_00341160((igSmartPointer<igObject> *)(&obj.w[5]), (short)(-1));
    FUN_00341160((igSmartPointer<igObject> *)(&obj.w[4]), (short)(-1));
    FUN_00341160((igSmartPointer<igObject> *)(&obj.w[3]), (short)(-1));
    FUN_0019c220(&obj.w[2], -1);
    FUN_00343260((igSmartPointer<igObject> *)(&obj.w[1]), -1);
    return r;
}

void beCameraBoxData_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beCameraBoxData_Register);
}

static igMetaObjectCallback g_beCameraBoxData_callbackList[] = { igSwitch_EnsureRegistered, igGeometryList_EnsureRegistered, igTransformList_EnsureRegistered, 0 };

void *beCameraBoxData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beCameraBoxData_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beCameraBoxData_GetMetaObjectFunction,
        "beCameraBoxData",
        0x1c, /* instance size */
        beCameraBoxData_GetVTable,
        beCameraBoxData_InitFields,
        0, /* extra callback item */
        g_beCameraBoxData_callbackList /* callback list */
    );
}

void beCameraBoxData_GetMetaObjectFunction(void)
{
    beCameraBoxData_GetMetaObject();
}

static FieldFactory g_beCameraBoxData_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beCameraBoxData_fieldTable[] = {
    "_switch",
    "_geometryList",
    "_transformList",
    "_eyePosList",
    "_intPosList",
};
static igMetaField **g_beCameraBoxData_fieldHandles[] = {
    &g_beCameraBoxData_switchMetaField,
    &g_beCameraBoxData_geometryListMetaField,
    &g_beCameraBoxData_transformListMetaField,
    &g_beCameraBoxData_eyePosListMetaField,
    &g_beCameraBoxData_intPosListMetaField,
};
static int g_beCameraBoxData_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
};

void beCameraBoxData_InitFields(void) {
    int base;
    void *switchField;
    void *geometryList;
    void *transformList;
    void *eyePosList;
    void *intPosList;
    void *meta;

    meta = (void *)g_beCameraBoxData_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beCameraBoxData_ctorTable, 5);
    switchField = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)switchField)->_metaObject = igSwitch_GetOrCreateMetaObject();
    geometryList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)geometryList)->_metaObject = igGeometryList_GetOrCreateMetaObject();
    ((igRefMetaField *)geometryList)->_construct = 1;
    transformList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)transformList)->_metaObject = igTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)transformList)->_construct = 1;
    eyePosList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)eyePosList)->_metaObject = igTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)eyePosList)->_construct = 1;
    intPosList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)intPosList)->_metaObject = igTransformList_GetOrCreateMetaObject();
    ((igRefMetaField *)intPosList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beCameraBoxData_fieldTable, g_beCameraBoxData_fieldHandles, g_beCameraBoxData_fieldOffsets, base);
}

