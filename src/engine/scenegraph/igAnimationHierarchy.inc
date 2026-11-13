igMetaObject *FUN_001a7100(void) {
    if (g_igAnimationHierarchy_metaObject[0] == 0) {
        g_igAnimationHierarchy_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAnimationHierarchy_metaObject[0];
}

igMetaObject *igAnimationHierarchy_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationHierarchy_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a71a0();
    return g_igAnimationHierarchy_metaObject[0];
}

void FUN_001a71a0(void)
{
    igMetaObject_RunStaticInit(igAnimationHierarchy_Register);
}

void igAnimationHierarchy_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igAnimationHierarchy_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimationHierarchy_GetMetaObject,
        igAnimationHierarchy_className,
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

void igAnimationHierarchy_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationHierarchy_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAnimationHierarchy_ctorTable[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_00187b10();
    ((igRefMetaField *)temp_s1)->_destruct = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)temp_s1)->_releaseOnReset = 1;
    igMetaObject_NameFields(temp_s0, &g_igAnimationHierarchy_fieldTable[0], &DAT_0048d170[0], &DAT_0048d178[0], temp_s2);
}

