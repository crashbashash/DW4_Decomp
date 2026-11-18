igMetaObject *g_igAnimationBindingList_metaObject;

igMetaObject *FUN_001a8ac0(void) {
    if (g_igAnimationBindingList_metaObject == 0) {
        g_igAnimationBindingList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAnimationBindingList_metaObject;
}

igMetaObject *igAnimationBindingList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationBindingList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationBindingList_EnsureRegistered();
    return g_igAnimationBindingList_metaObject;
}

int igAnimationBindingList_GetVTable(void) {
    struct Obj_1a8b60 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationBindingList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAnimationBindingList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationBindingList_Register);
}

static igMetaObjectCallback g_igAnimationBindingList_callbackList[] = { igAnimationBinding_EnsureRegistered, 0 };

CallbackArray *igAnimationBindingList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationBindingList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationBindingList_GetMetaObject,
        "igAnimationBindingList",
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

