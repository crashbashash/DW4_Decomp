int FUN_001a8f80(void) {
    if (DAT_00562368[0] == 0) {
        DAT_00562368[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562368[0];
}

igMetaObject *igAnimationList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9060();
    return g_igAnimationList_metaObject[0];
}

int igAnimationList_GetVTable(void) {
    struct Obj_1a9020 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00529b00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001a9060(void)
{
    igMetaObject_RunStaticInit(igAnimationList_Register);
}

void igAnimationList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAnimationList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationList_GetMetaObject,
        igAnimationList_className,
        0x14, /* instance size */
        igAnimationList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationList_callbackList /* callback list */
    );
}

void thunk_igAnimationList_GetMetaObject(void) {
    igAnimationList_GetMetaObject();
}

