igMetaObject *g_igAnimationList_metaObject;

igMetaObject *igAnimationList_GetOrCreateMetaObject(void) {
    if (g_igAnimationList_metaObject == 0) {
        g_igAnimationList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationList_metaObject;
}

igMetaObject *igAnimationList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationList_EnsureRegistered();
    return g_igAnimationList_metaObject;
}

int igAnimationList_GetVTable(void) {
    struct Obj_1a9020 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAnimationList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationList_Register);
}

static igMetaObjectCallback g_igAnimationList_callbackList[] = { igAnimation_EnsureRegistered, 0 };

CallbackArray *igAnimationList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAnimationList_GetMetaObjectFunction,
        "igAnimationList",
        0x14, /* instance size */
        igAnimationList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationList_callbackList /* callback list */
    );
}

void igAnimationList_GetMetaObjectFunction(void) {
    igAnimationList_GetMetaObject();
}

