igMetaObject *g_igAnimationCombinerBoneInfoList_metaObject;

igMetaObject *igAnimationCombinerBoneInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationCombinerBoneInfoList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationCombinerBoneInfoList_EnsureRegistered();
    return g_igAnimationCombinerBoneInfoList_metaObject;
}

int igAnimationCombinerBoneInfoList_GetVTable(void) {
    struct Obj_1a7fe0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAnimationCombinerBoneInfoList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igAnimationCombinerBoneInfoList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAnimationCombinerBoneInfoList_Register);
}

static igMetaObjectCallback g_igAnimationCombinerBoneInfoList_callbackList[] = { igAnimationCombinerBoneInfo_EnsureRegistered, 0 };

CallbackArray *igAnimationCombinerBoneInfoList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAnimationCombinerBoneInfoList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igAnimationCombinerBoneInfoList_GetMetaObjectFunction,
        "igAnimationCombinerBoneInfoList",
        0x14, /* instance size */
        igAnimationCombinerBoneInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationCombinerBoneInfoList_callbackList /* callback list */
    );
}

void igAnimationCombinerBoneInfoList_GetMetaObjectFunction(void) {
    igAnimationCombinerBoneInfoList_GetMetaObject();
}

