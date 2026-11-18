igMetaObject *g_igAnimationCombinerList_metaObject;

igMetaObject *FUN_001a83b0(void) {
    if (g_igAnimationCombinerList_metaObject == 0) {
        g_igAnimationCombinerList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationCombinerList_metaObject;
}

igMetaObject *igAnimationCombinerList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationCombinerList_EnsureRegistered();
    return g_igAnimationCombinerList_metaObject;
}

int igAnimationCombinerList_GetVTable(void) {
    struct Obj_1a8450 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationCombinerList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAnimationCombinerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerList_Register);
}

static igMetaObjectCallback g_igAnimationCombinerList_callbackList[] = { igAnimationCombiner_EnsureRegistered, 0 };

CallbackArray *igAnimationCombinerList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationCombinerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationCombinerList_GetMetaObject,
        "igAnimationCombinerList",
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

