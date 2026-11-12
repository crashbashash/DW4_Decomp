igMetaObject *FUN_001a6600(void) {
    if (g_igAnimationSystem_metaObject[0] == 0) {
        g_igAnimationSystem_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAnimationSystem_metaObject[0];
}

igMetaObject *igAnimationSystem_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationSystem_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a66a0();
    return g_igAnimationSystem_metaObject[0];
}

void FUN_001a66a0(void)
{
    igMetaObject_RunStaticInit(igAnimationSystem_Register);
}

void igAnimationSystem_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igAnimationSystem_metaObject),
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimationSystem_GetMetaObject,
        igAnimationSystem_className,
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

void igAnimationSystem_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationSystem_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_0048cee0[0], 1);
    temp_s1 = (void *)(((void *)igMetaObject_GetFieldAt(temp_s0, temp_s2)));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001a7100();
    igMetaObject_NameFields(temp_s0, &DAT_0048cee8[0], &DAT_0048cef0[0], &DAT_0048cef8[0], temp_s2);
}

