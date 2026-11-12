igMetaObject *igAnimationCombinerBoneInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8020();
    return g_igAnimationCombinerBoneInfoList_metaObject[0];
}

int igAnimationCombinerBoneInfoList_GetVTable(void) {
    struct Obj_1a7fe0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529d90[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001a8020(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerBoneInfoList_Register);
}

void igAnimationCombinerBoneInfoList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationCombinerBoneInfoList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationCombinerBoneInfoList_GetMetaObject,
        igAnimationCombinerBoneInfoList_className,
        0x14, /* instance size */
        igAnimationCombinerBoneInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfoList_callbackList /* callback list */
    );
}

void thunk_igAnimationCombinerBoneInfoList_GetMetaObject(void) {
    igAnimationCombinerBoneInfoList_GetMetaObject();
}

