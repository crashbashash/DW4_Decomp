igMetaObject *FUN_001a72d0(void) {
    if (g_igAnimationModifierList_metaObject[0] == 0) {
        g_igAnimationModifierList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAnimationModifierList_metaObject[0];
}

igMetaObject *igAnimationModifierList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationModifierList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a73b0();
    return g_igAnimationModifierList_metaObject[0];
}

int igAnimationModifierList_GetVTable(void) {
    struct Obj_1a7370 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529f40[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a73b0(void)
{
    igMetaObject_RunStaticInit(igAnimationModifierList_Register);
}

void igAnimationModifierList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationModifierList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationModifierList_GetMetaObject,
        igAnimationModifierList_className,
        0x14, /* instance size */
        igAnimationModifierList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationModifierList_callbackList /* callback list */
    );
}

void thunk_igAnimationModifierList_GetMetaObject(void) {
    igAnimationModifierList_GetMetaObject();
}

