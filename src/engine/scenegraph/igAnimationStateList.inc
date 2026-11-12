int FUN_001a6920(void) {
    if (DAT_005620e0[0] == 0) {
        DAT_005620e0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005620e0[0];
}

igMetaObject *igAnimationStateList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationStateList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a6a00();
    return g_igAnimationStateList_metaObject[0];
}

int igAnimationStateList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00529fb0[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_001a6a00(void)
{
    igMetaObject_RunStaticInit(igAnimationStateList_Register);
}

void igAnimationStateList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationStateList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationStateList_GetMetaObject,
        igAnimationStateList_className,
        0x14, /* instance size */
        igAnimationStateList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationStateList_callbackList /* callback list */
    );
}

void thunk_igAnimationStateList_GetMetaObject(void) {
    igAnimationStateList_GetMetaObject();
}

