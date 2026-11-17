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
    r = *(int *)((char *)&o + *(int *)((char *)g_objectSystem + 916));
    o.vt = &g_igLod_vtable[0];
    igSmartPointer_igFloatList_Destruct(&o.f[15], -1);
    igSmartPointer_igNode_Destruct((ObjectRefWord *)p17, -1);
    igSmartPointer_igFloatList_Destruct(p16, -1);
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
        thunk_igLod_GetMetaObject,
        "igLod",
        0x44, /* instance size */
        igLod_GetVTable,
        &igLod_InitFields,
        0, /* extra callback item */
        g_igLod_callbackList /* callback list */
    );
}

void thunk_igLod_GetMetaObject(void) {
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
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s1;
    int temp_s0;
    int sp40[3];
    void *temp_a0;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;

    temp_s1 = (void *)g_igLod_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igLod_ctorTable, 7);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    ((igMetaField *)temp_s2)->_deepCopyMethod = 0;
    ((igMetaField *)temp_s2)->_shallowCopyMethod = 2;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igNode_GetOrCreateMetaObject();
    ((igMetaField *)temp_s2_2)->_persistent = 0;
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    igIntMetaField_SetDefault((void **)temp_v0, -1);
    ((igIntMetaField *)temp_v0)->_persistent = 0;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    igFloatMetaField_SetDefault((void **)temp_v0_2, 0.0f);
    ((igFloatMetaField *)temp_v0_2)->_persistent = 0;
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 4)));
    igFloatMetaField_SetDefault((void **)temp_v0_3, 0.0f);
    ((igFloatMetaField *)temp_v0_3)->_persistent = 0;
    temp_a0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 5)));
    sp40[0] = 0;
    sp40[1] = 0;
    sp40[2] = 0;
    igVec3fMetaField_SetDefault(temp_a0, sp40);
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 6)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igFloatList_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igLod_fieldTable, g_igLod_fieldHandles, g_igLod_fieldOffsets, temp_s0);
}

