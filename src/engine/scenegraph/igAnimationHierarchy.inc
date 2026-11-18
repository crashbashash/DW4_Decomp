igMetaObject *igAnimationHierarchy_GetOrCreateMetaObject(void) {
    if (g_igAnimationHierarchy_metaObject == 0) {
        g_igAnimationHierarchy_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationHierarchy_metaObject;
}

igMetaObject *igAnimationHierarchy_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationHierarchy_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationHierarchy_EnsureRegistered();
    return g_igAnimationHierarchy_metaObject;
}

void igAnimationHierarchy_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationHierarchy_Register);
}

CallbackArray *igAnimationHierarchy_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAnimationHierarchy_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igAnimationHierarchy_GetMetaObjectFunction,
        "igAnimationHierarchy",
        0x10, /* instance size */
        0,
        &igAnimationHierarchy_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAnimationHierarchy_GetMetaObjectFunction(void) {
    igAnimationHierarchy_GetMetaObject();
}

static FieldFactory g_igAnimationHierarchy_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
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
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igAnimationHierarchy_ctorTable, 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2)));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_00187b10();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igAnimationHierarchy_fieldTable, g_igAnimationHierarchy_fieldHandles, g_igAnimationHierarchy_fieldOffsets, temp_s2);
}

