igMetaObject *FUN_001a7100(void) {
    if (g_igAnimationHierarchy_metaObject == 0) {
        g_igAnimationHierarchy_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAnimationHierarchy_metaObject;
}

igMetaObject *igAnimationHierarchy_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationHierarchy_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a71a0();
    return g_igAnimationHierarchy_metaObject;
}

void FUN_001a71a0(void)
{
    igMetaObject_RunStaticInit(igAnimationHierarchy_Register);
}

void igAnimationHierarchy_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAnimationHierarchy_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimationHierarchy_GetMetaObject,
        "igAnimationHierarchy",
        0x10, /* instance size */
        0,
        &igAnimationHierarchy_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAnimationHierarchy_GetMetaObject(void) {
    igAnimationHierarchy_GetMetaObject();
}

static FieldFactory g_igAnimationHierarchy_ctorTable[] = {
    igMemoryRefMetaField_Create,
};
static const char *g_igAnimationHierarchy_fieldTable[] = {
    "_boneTranslationArray",
};
static igMetaField **g_igAnimationHierarchy_fieldHandles[] = {
    &g_igAnimationHierarchy_boneTranslationArrayMetaField,
};
static int g_igAnimationHierarchy_fieldOffsets[] = {
    12,
};

void igAnimationHierarchy_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationHierarchy_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationHierarchy_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_00187b10();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationHierarchy_fieldTable, g_igAnimationHierarchy_fieldHandles, g_igAnimationHierarchy_fieldOffsets, temp_s2);
}

