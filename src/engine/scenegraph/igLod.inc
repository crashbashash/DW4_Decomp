igMetaObject *g_igLod_metaObject;
igMetaField *g_igLod_rangeListMetaField;
igMetaField *g_igLod_lastRangeMetaField;
igMetaField *g_igLod_lastIndexMetaField;
igMetaField *g_igLod_lastLowerMetaField;
igMetaField *g_igLod_lastUpperMetaField;
igMetaField *g_igLod_centerMetaField;
igMetaField *g_igLod_hysteresisListMetaField;

igMetaObject *igLod_GetMetaObject(void)
{
    igMetaObject *g = g_igLod_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLod_EnsureRegistered();
    return g_igLod_metaObject;
}

int igLod_GetVTable(void) {
    struct W_19d660 o;
    int *p16;
    int r;
    int *p17;
    igObject_InitHeader((igObject *)&o);
    o.f[1] = 0;
    o.f[2] = 0;
    o.f[3] = 0;
    o.f[6] = 0;
    o.vt = &g_igLod_vtable[0];
    p16 = &o.f[7];
    *p16 = 0;
    p17 = &o.f[8];
    *p17 = 0;
    o.f[15] = 0;
    r = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = &g_igLod_vtable[0];
    igSmartPointer_igFloatList_Destruct((igSmartPointer<igObject> *)&o.f[15], -1);
    igSmartPointer_igNode_Destruct((igSmartPointer<igObject> *)p17, -1);
    igSmartPointer_igFloatList_Destruct((igSmartPointer<igObject> *)p16, -1);
    igGroup_Destroy((igGroup *)&o, 0);
    return r;
}

void igLod_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLod_Register);
}

static igMetaObjectCallback g_igLod_callbackList[] = { igFloatList_EnsureRegistered, igNode_EnsureRegistered, 0 };

CallbackArray *igLod_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLod_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        igLod_GetMetaObjectFunction,
        "igLod",
        0x44, /* instance size */
        igLod_GetVTable,
        &igLod_InitFields,
        0, /* extra callback item */
        g_igLod_callbackList /* callback list */
    );
}

void igLod_GetMetaObjectFunction(void) {
    igLod_GetMetaObject();
}

static FieldFactory g_igLod_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igFloatMetaField_Create,
    (FieldFactory)igVec3fMetaField_CreateInstance,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igLod_fieldTable[] = {
    "_rangeList",
    "_lastRange",
    "_lastIndex",
    "_lastLower",
    "_lastUpper",
    "_center",
    "_hysteresisList",
};
static igMetaField **g_igLod_fieldHandles[] = {
    &g_igLod_rangeListMetaField,
    &g_igLod_lastRangeMetaField,
    &g_igLod_lastIndexMetaField,
    &g_igLod_lastLowerMetaField,
    &g_igLod_lastUpperMetaField,
    &g_igLod_centerMetaField,
    &g_igLod_hysteresisListMetaField,
};
static int g_igLod_fieldOffsets[] = {
    32,
    36,
    40,
    44,
    48,
    52,
    64,
};

void igLod_InitFields(void) {
    void *rangeListField;
    void *lastRangeField;
    void *hysteresisListField;
    void *meta;
    int base;
    int defaultCenter[3];
    void *centerField;
    void *lastIndexField;
    void *lastLowerField;
    void *lastUpperField;

    meta = (void *)g_igLod_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igLod_ctorTable, 7);
    rangeListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)rangeListField)->_metaObject = (int)igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)rangeListField)->_construct = 1;
    ((igMetaField *)rangeListField)->_deepCopyMethod = 0;
    ((igMetaField *)rangeListField)->_shallowCopyMethod = 2;
    lastRangeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)lastRangeField)->_metaObject = (int)igNode_GetOrCreateMetaObject();
    ((igMetaField *)lastRangeField)->_persistent = 0;
    lastIndexField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    igIntMetaField_SetDefault((igMetaField *)lastIndexField, -1);
    ((igIntMetaField *)lastIndexField)->_persistent = 0;
    lastLowerField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    igFloatMetaField_SetDefault((igMetaField *)lastLowerField, 0.0f);
    ((igFloatMetaField *)lastLowerField)->_persistent = 0;
    lastUpperField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    igFloatMetaField_SetDefault((igMetaField *)lastUpperField, 0.0f);
    ((igFloatMetaField *)lastUpperField)->_persistent = 0;
    centerField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)));
    defaultCenter[0] = 0;
    defaultCenter[1] = 0;
    defaultCenter[2] = 0;
    igVec3fMetaField_SetDefault((igMetaField *)centerField, (const float *)defaultCenter);
    hysteresisListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)hysteresisListField)->_metaObject = (int)igFloatList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igLod_fieldTable, g_igLod_fieldHandles, g_igLod_fieldOffsets, base);
}

