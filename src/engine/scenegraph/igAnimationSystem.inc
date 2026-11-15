igMetaObject *g_igAnimationSystem_metaObject;
igMetaField *g_igAnimationSystem_animHierarchyMetaField;

igMetaObject *FUN_001a6600(void) {
    if (g_igAnimationSystem_metaObject == 0) {
        g_igAnimationSystem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAnimationSystem_metaObject;
}

igMetaObject *igAnimationSystem_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationSystem_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a66a0();
    return g_igAnimationSystem_metaObject;
}

void FUN_001a66a0(void)
{
    igMetaObject_RunStaticInit(igAnimationSystem_Register);
}

static igMetaObjectCallback g_igAnimationSystem_callbackList[] = { FUN_001a71a0, 0 };

void igAnimationSystem_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAnimationSystem_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimationSystem_GetMetaObject,
        "igAnimationSystem",
        0x10, /* instance size */
        0,
        &igAnimationSystem_InitFields,
        0, /* extra callback item */
        g_igAnimationSystem_callbackList /* callback list */
    );
}

void thunk_igAnimationSystem_GetMetaObject(void) {
    igAnimationSystem_GetMetaObject();
}

static FieldFactory g_igAnimationSystem_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igAnimationSystem_fieldTable[] = {
    "_animHierarchy",
};
static igMetaField **g_igAnimationSystem_fieldHandles[] = {
    &g_igAnimationSystem_animHierarchyMetaField,
};
static int g_igAnimationSystem_fieldOffsets[] = {
    12,
};

void igAnimationSystem_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationSystem_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationSystem_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a7100();
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationSystem_fieldTable, g_igAnimationSystem_fieldHandles, g_igAnimationSystem_fieldOffsets, temp_s2);
}

