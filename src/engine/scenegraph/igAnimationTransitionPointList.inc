igMetaObject *g_igAnimationTransitionPointList_metaObject;

igMetaObject *FUN_001a9830(void) {
    if (g_igAnimationTransitionPointList_metaObject == 0) {
        g_igAnimationTransitionPointList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationTransitionPointList_metaObject;
}

igMetaObject *igAnimationTransitionPointList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionPointList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a9910();
    return g_igAnimationTransitionPointList_metaObject;
}

int igAnimationTransitionPointList_GetVTable(void) {
    struct Obj_1a98d0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationTransitionPointList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_001a9910(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionPointList_Register);
}

static igMetaObjectCallback g_igAnimationTransitionPointList_callbackList[] = { FUN_001a9a80, 0 };

CallbackArray *igAnimationTransitionPointList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTransitionPointList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationTransitionPointList_GetMetaObject,
        "igAnimationTransitionPointList",
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

