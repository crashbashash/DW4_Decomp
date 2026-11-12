int FUN_001a9830(void) {
    if (DAT_005623e0[0] == 0) {
        DAT_005623e0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005623e0[0];
}

igMetaObject *igAnimationTransitionPointList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionPointList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9910();
    return g_igAnimationTransitionPointList_metaObject[0];
}

int igAnimationTransitionPointList_GetVTable(void) {
    struct Obj_1a98d0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005299c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001a9910(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionPointList_Register);
}

void igAnimationTransitionPointList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationTransitionPointList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationTransitionPointList_GetMetaObject,
        igAnimationTransitionPointList_className,
        0x14, /* instance size */
        igAnimationTransitionPointList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationTransitionPointList_callbackList /* callback list */
    );
}

void thunk_igAnimationTransitionPointList_GetMetaObject(void) {
    igAnimationTransitionPointList_GetMetaObject();
}

