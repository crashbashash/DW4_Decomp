igMetaObject *g_igAnimationCombinerBoneInfoPool_metaObject;

int igAnimationCombinerBoneInfoPool_Create(int allocator) {
    igAnimationCombinerBoneInfoPool_RunStaticInit();
    return igMetaObject_CreateInstance(g_igAnimationCombinerBoneInfoPool_metaObject, allocator);
}

igMetaObject *igAnimationCombinerBoneInfoPool_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfoPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationCombinerBoneInfoPool_RunStaticInit();
    return g_igAnimationCombinerBoneInfoPool_metaObject;
}

int igAnimationCombinerBoneInfoPool_GetVTable(void) {
    struct Obj_1a7d50 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igAnimationCombinerBoneInfoPool_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igAnimationCombinerBoneInfoPool_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerBoneInfoPool_Register);
}

static igMetaObjectCallback g_igAnimationCombinerBoneInfoPool_callbackList[] = { FUN_001a8220, 0 };

void igAnimationCombinerBoneInfoPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationCombinerBoneInfoPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        thunk_igAnimationCombinerBoneInfoPool_GetMetaObject,
        "igAnimationCombinerBoneInfoPool",
        0x20, /* instance size */
        igAnimationCombinerBoneInfoPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfoPool_callbackList /* callback list */
    );
}

void thunk_igAnimationCombinerBoneInfoPool_GetMetaObject(void) {
    igAnimationCombinerBoneInfoPool_GetMetaObject();
}

