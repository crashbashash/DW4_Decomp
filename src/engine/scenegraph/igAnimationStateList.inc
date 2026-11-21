igMetaObject *g_igAnimationStateList_metaObject;

igMetaObject *igAnimationStateList_GetOrCreateMetaObject(void) {
    if (g_igAnimationStateList_metaObject == 0) {
        g_igAnimationStateList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationStateList_metaObject;
}

igMetaObject *igAnimationStateList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationStateList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationStateList_EnsureRegistered();
    return g_igAnimationStateList_metaObject;
}

int igAnimationStateList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igAnimationStateList_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igAnimationStateList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationStateList_Register);
}

static igMetaObjectCallback g_igAnimationStateList_callbackList[] = { igAnimationState_EnsureRegistered, 0 };

CallbackArray *igAnimationStateList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationStateList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igAnimationStateList_GetMetaObjectFunction,
        "igAnimationStateList",
        0x14, /* instance size */
        igAnimationStateList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationStateList_callbackList /* callback list */
    );
}

void igAnimationStateList_GetMetaObjectFunction(void) {
    igAnimationStateList_GetMetaObject();
}

