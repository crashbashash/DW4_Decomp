igMetaObject *g_igAnimationCombinerBoneInfoListList_metaObject;

igMetaObject *FUN_001a7e20(void) {
    if (g_igAnimationCombinerBoneInfoListList_metaObject == 0) {
        g_igAnimationCombinerBoneInfoListList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationCombinerBoneInfoListList_metaObject;
}

igMetaObject *igAnimationCombinerBoneInfoListList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfoListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationCombinerBoneInfoListList_EnsureRegistered();
    return g_igAnimationCombinerBoneInfoListList_metaObject;
}

int igAnimationCombinerBoneInfoListList_GetVTable(void) {
    struct Obj_1a7ec0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationCombinerBoneInfoListList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAnimationCombinerBoneInfoListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerBoneInfoListList_Register);
}

static igMetaObjectCallback g_igAnimationCombinerBoneInfoListList_callbackList[] = { igAnimationCombinerBoneInfoList_EnsureRegistered, 0 };

CallbackArray *igAnimationCombinerBoneInfoListList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationCombinerBoneInfoListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationCombinerBoneInfoListList_GetMetaObject,
        "igAnimationCombinerBoneInfoListList",
        0x14, /* instance size */
        igAnimationCombinerBoneInfoListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfoListList_callbackList /* callback list */
    );
}

void thunk_igAnimationCombinerBoneInfoListList_GetMetaObject(void) {
    igAnimationCombinerBoneInfoListList_GetMetaObject();
}

