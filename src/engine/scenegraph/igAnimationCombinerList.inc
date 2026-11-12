igMetaObject *FUN_001a83b0(void) {
    if (g_igAnimationCombinerList_metaObject[0] == 0) {
        g_igAnimationCombinerList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAnimationCombinerList_metaObject[0];
}

igMetaObject *igAnimationCombinerList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8490();
    return g_igAnimationCombinerList_metaObject[0];
}

int igAnimationCombinerList_GetVTable(void) {
    struct Obj_1a8450 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529cc0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a8490(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerList_Register);
}

void igAnimationCombinerList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationCombinerList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationCombinerList_GetMetaObject,
        igAnimationCombinerList_className,
        0x14, /* instance size */
        igAnimationCombinerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerList_callbackList /* callback list */
    );
}

void thunk_igAnimationCombinerList_GetMetaObject(void) {
    igAnimationCombinerList_GetMetaObject();
}

