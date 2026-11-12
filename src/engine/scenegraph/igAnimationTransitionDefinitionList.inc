int FUN_001a9420(void) {
    if (DAT_005623b8[0] == 0) {
        DAT_005623b8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005623b8[0];
}

igMetaObject *igAnimationTransitionDefinitionList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionDefinitionList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9500();
    return g_igAnimationTransitionDefinitionList_metaObject[0];
}

int igAnimationTransitionDefinitionList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_00529a90[0];
    off = *(int *)((char *)(((int * *)DAT_00586dc8)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_001a9500(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionDefinitionList_Register);
}

void igAnimationTransitionDefinitionList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationTransitionDefinitionList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationTransitionDefinitionList_GetMetaObject,
        igAnimationTransitionDefinitionList_className,
        0x14, /* instance size */
        igAnimationTransitionDefinitionList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationTransitionDefinitionList_callbackList /* callback list */
    );
}

void thunk_igAnimationTransitionDefinitionList_GetMetaObject(void) {
    igAnimationTransitionDefinitionList_GetMetaObject();
}

