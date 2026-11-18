igMetaObject *g_igAnimationTransitionDefinitionList_metaObject;

igMetaObject *igAnimationTransitionDefinitionList_GetOrCreateMetaObject(void) {
    if (g_igAnimationTransitionDefinitionList_metaObject == 0) {
        g_igAnimationTransitionDefinitionList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationTransitionDefinitionList_metaObject;
}

igMetaObject *igAnimationTransitionDefinitionList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationTransitionDefinitionList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationTransitionDefinitionList_EnsureRegistered();
    return g_igAnimationTransitionDefinitionList_metaObject;
}

int igAnimationTransitionDefinitionList_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igAnimationTransitionDefinitionList_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igAnimationTransitionDefinitionList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationTransitionDefinitionList_Register);
}

static igMetaObjectCallback g_igAnimationTransitionDefinitionList_callbackList[] = { igAnimationTransitionDefinition_EnsureRegistered, 0 };

CallbackArray *igAnimationTransitionDefinitionList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationTransitionDefinitionList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAnimationTransitionDefinitionList_GetMetaObjectFunction,
        "igAnimationTransitionDefinitionList",
        0x14, /* instance size */
        igAnimationTransitionDefinitionList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationTransitionDefinitionList_callbackList /* callback list */
    );
}

void igAnimationTransitionDefinitionList_GetMetaObjectFunction(void) {
    igAnimationTransitionDefinitionList_GetMetaObject();
}

