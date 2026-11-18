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

igMetaObject *igAnimation_GetOrCreateMetaObject(void) {
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
    igSmartPointer_igBitMask_Destruct((igSmartPointer<igObject> *)&u.b[56], -1);
    igSmartPointer_igAnimationTransitionDefinitionList_Destruct((igSmartPointer<igObject> *)p104, -1);
    igSmartPointer_igAnimationTrackList_Destruct((igSmartPointer<igObject> *)p100, -1);
    igSmartPointer_igAnimationBindingList_Destruct((igSmartPointer<igObject> *)p96, -1);
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
        igAnimation_GetMetaObjectFunction,
        "igAnimation",
        0x40, /* instance size */
        igAnimation_GetVTable,
        &igAnimation_InitFields,
        0, /* extra callback item */
        g_igAnimation_callbackList /* callback list */
    );
}

void igAnimation_GetMetaObjectFunction(void) {
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
    int base;
    void *bindingListField;
    void *trackListField;
    void *transitionListField;
    void *useAnimationTransBoolArrayField;
    void *meta;

    meta = (void *)g_igAnimation_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igAnimation_ctorTable, 8);
    bindingListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)bindingListField)->_metaObject = (int)igAnimationBindingList_GetOrCreateMetaObject();
    ((igRefMetaField *)bindingListField)->_construct = 1;
    trackListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)trackListField)->_metaObject = (int)igAnimationTrackList_GetOrCreateMetaObject();
    ((igRefMetaField *)trackListField)->_construct = 1;
    transitionListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)transitionListField)->_metaObject = (int)igAnimationTransitionDefinitionList_GetOrCreateMetaObject();
    ((igRefMetaField *)transitionListField)->_construct = 1;
    useAnimationTransBoolArrayField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7)));
    ((igObjectRefMetaField *)useAnimationTransBoolArrayField)->_metaObject = (int)igBitMask_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, g_igAnimation_fieldTable, g_igAnimation_fieldHandles, g_igAnimation_fieldOffsets, base);
}

