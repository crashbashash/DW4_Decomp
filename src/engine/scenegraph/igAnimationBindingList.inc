igMetaObject *FUN_001a8ac0(void) {
    if (g_igAnimationBindingList_metaObject[0] == 0) {
        g_igAnimationBindingList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAnimationBindingList_metaObject[0];
}

igMetaObject *igAnimationBindingList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationBindingList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a8ba0();
    return g_igAnimationBindingList_metaObject[0];
}

int igAnimationBindingList_GetVTable(void) {
    struct Obj_1a8b60 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529bd0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a8ba0(void)
{
    igMetaObject_RunStaticInit(igAnimationBindingList_Register);
}

void igAnimationBindingList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationBindingList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationBindingList_GetMetaObject,
        igAnimationBindingList_className,
        0x14, /* instance size */
        igAnimationBindingList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationBindingList_callbackList /* callback list */
    );
}

void thunk_igAnimationBindingList_GetMetaObject(void) {
    igAnimationBindingList_GetMetaObject();
}

