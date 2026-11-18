int FUN_001a90f0(int arg0) {
    igAnimation_EnsureRegistered();
    return (int)igMetaObject_CreateInstance((igMetaObject *)g_igAnimation_metaObject, (igMemoryPoolView *)arg0);
}

igMetaObject *g_igAnimation_metaObject;
igMetaField *g_igAnimation_priorityMetaField;
igMetaField *g_igAnimation_bindingListMetaField;
igMetaField *g_igAnimation_trackListMetaField;
igMetaField *g_igAnimation_transitionListMetaField;
igMetaField *g_igAnimation_keyFrameTimeOffsetMetaField;
igMetaField *g_igAnimation_startTimeMetaField;
igMetaField *g_igAnimation_durationMetaField;
igMetaField *g_igAnimation_useAnimationTransBoolArrayMetaField;

igMetaObject *FUN_001a9130(void) {
    if (g_igAnimation_metaObject == 0) {
        g_igAnimation_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimation_metaObject;
}

igMetaObject *igAnimation_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimation_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimation_EnsureRegistered();
    return g_igAnimation_metaObject;
}

int igAnimation_GetVTable(void) {
    union U_1a91d0 u;
    int temp_s;
    char *p104;
    char *p100;
    char *p96;
    igObject_InitHeader((igObject *)u.b);
    u.vt = (int)&g_igAnimation_vtable[0];
    *(int *)&u.b[8] = 0;
    p96 = &u.b[16];
    *(int *)p96 = 0;
    p100 = &u.b[20];
    *(int *)p100 = 0;
    p104 = &u.b[24];
    *(int *)p104 = 0;
    *(int *)&u.b[56] = 0;
    temp_s = *(int *)&u.b[g_objectSystem->vtableProbeOffset];
    u.vt = (int)&g_igAnimation_vtable[0];
    FUN_00196a50((struct R * *)&u.b[56], -1);
    FUN_0019de50((struct Ref * *)p104, -1);
    FUN_0019ded0((void * *)p100, -1);
    FUN_0019df50((O *)p96, -1);
    igNamedObject_Destroy((igNamedObject *)u.b, 0);
    return temp_s;
}

void igAnimation_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimation_Register);
}

static igMetaObjectCallback g_igAnimation_callbackList[] = { igAnimationBindingList_EnsureRegistered, igAnimationTrackList_EnsureRegistered, igAnimationTransitionDefinitionList_EnsureRegistered, igBitMask_EnsureRegistered, 0 };

CallbackArray *igAnimation_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimation_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimation_GetMetaObject,
        "igAnimation",
        0x40, /* instance size */
        igAnimation_GetVTable,
        &igAnimation_InitFields,
        0, /* extra callback item */
        g_igAnimation_callbackList /* callback list */
    );
}

void thunk_igAnimation_GetMetaObject(void) {
    igAnimation_GetMetaObject();
}

static FieldFactory g_igAnimation_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igLongMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAnimation_fieldTable[] = {
    "_priority",
    "_bindingList",
    "_trackList",
    "_transitionList",
    "_keyFrameTimeOffset",
    "_startTime",
    "_duration",
    "_useAnimationTransBoolArray",
};
static igMetaField **g_igAnimation_fieldHandles[] = {
    &g_igAnimation_priorityMetaField,
    &g_igAnimation_bindingListMetaField,
    &g_igAnimation_trackListMetaField,
    &g_igAnimation_transitionListMetaField,
    &g_igAnimation_keyFrameTimeOffsetMetaField,
    &g_igAnimation_startTimeMetaField,
    &g_igAnimation_durationMetaField,
    &g_igAnimation_useAnimationTransBoolArrayMetaField,
};
static int g_igAnimation_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    32,
    40,
    48,
    56,
};

void igAnimation_InitFields(void) {
    int temp_s0;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s1;

    temp_s1 = (void *)g_igAnimation_metaObject;
    temp_s0 = igMetaObject_GetFieldCount((igMetaObject *)temp_s1);
    igMetaObject_CreateFields((igMetaObject *)temp_s1, g_igAnimation_ctorTable, 8);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)FUN_001a8ac0();
    ((igRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 2)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)FUN_001a9d90();
    ((igRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 3)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)FUN_001a9420();
    ((igRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s1, temp_s0 + 7)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)FUN_001a4d90();
    igMetaObject_NameFields((igMetaObject *)temp_s1, g_igAnimation_fieldTable, g_igAnimation_fieldHandles, g_igAnimation_fieldOffsets, temp_s0);
}

