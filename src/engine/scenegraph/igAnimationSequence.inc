igMetaObject *igAnimationSequence_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationSequence_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7080();
    return g_igAnimationSequence_metaObject;
}

void FUN_001a7080(void)
{
    igMetaObject_RunStaticInit(igAnimationSequence_Register);
}

CallbackArray *igAnimationSequence_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAnimationSequence_metaObject,
        igTransformSource_Register,
        igTransformSource_GetPublishedMetaObject,
        thunk_igAnimationSequence_GetMetaObject,
        "igAnimationSequence",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igAnimationSequence_GetMetaObject(void) {
    igAnimationSequence_GetMetaObject();
}

