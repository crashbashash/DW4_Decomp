igMetaObject *FUN_001a9bb0(void) {
    if (g_igAnimationTransitionParams_metaObject[0] == 0) {
        g_igAnimationTransitionParams_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAnimationTransitionParams_metaObject[0];
}

igMetaObject *igAnimationTransitionParams_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionParams_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9c90();
    return g_igAnimationTransitionParams_metaObject[0];
}

int igAnimationTransitionParams_GetVTable(void) {
    struct Obj_1a9c50 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529900[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a9c90(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionParams_Register);
}

void igAnimationTransitionParams_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationTransitionParams_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionParams_GetMetaObject,
        igAnimationTransitionParams_className,
        0x20, /* instance size */
        igAnimationTransitionParams_GetVTable,
        &igAnimationTransitionParams_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAnimationTransitionParams_GetMetaObject(void) {
    igAnimationTransitionParams_GetMetaObject();
}

void igAnimationTransitionParams_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igAnimationTransitionParams_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_igAnimationTransitionParams_ctorTable[0], 4);
    igMetaObject_NameFields(temp_s0, &g_igAnimationTransitionParams_fieldTable[0], &DAT_0048d640[0], &DAT_0048d650[0], temp_s1);
}

