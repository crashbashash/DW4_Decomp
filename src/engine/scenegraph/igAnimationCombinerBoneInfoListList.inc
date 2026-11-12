int FUN_001a7e20(void) {
    if (DAT_00562258[0] == 0) {
        DAT_00562258[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562258[0];
}

igMetaObject *igAnimationCombinerBoneInfoListList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfoListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7f00();
    return g_igAnimationCombinerBoneInfoListList_metaObject[0];
}

int igAnimationCombinerBoneInfoListList_GetVTable(void) {
    struct Obj_1a7ec0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529e00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001a7f00(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerBoneInfoListList_Register);
}

void igAnimationCombinerBoneInfoListList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationCombinerBoneInfoListList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationCombinerBoneInfoListList_GetMetaObject,
        igAnimationCombinerBoneInfoListList_className,
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

