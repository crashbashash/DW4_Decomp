igMetaObject *g_igAnimationModifierList_metaObject;

igMetaObject *FUN_001a72d0(void) {
    if (g_igAnimationModifierList_metaObject == 0) {
        g_igAnimationModifierList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationModifierList_metaObject;
}

igMetaObject *igAnimationModifierList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationModifierList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationModifierList_EnsureRegistered();
    return g_igAnimationModifierList_metaObject;
}

int igAnimationModifierList_GetVTable(void) {
    struct Obj_1a7370 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationModifierList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAnimationModifierList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationModifierList_Register);
}

static igMetaObjectCallback g_igAnimationModifierList_callbackList[] = { FUN_001a7600, 0 };

CallbackArray *igAnimationModifierList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationModifierList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationModifierList_GetMetaObject,
        "igAnimationModifierList",
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

