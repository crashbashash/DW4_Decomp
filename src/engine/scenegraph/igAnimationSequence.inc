igMetaObject *igAnimationSequence_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationSequence_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAnimationSequence_EnsureRegistered();
    return g_igAnimationSequence_metaObject;
}

void igAnimationSequence_EnsureRegistered(void)
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
        igAnimationSequence_GetMetaObjectFunction,
        "igAnimationSequence",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAnimationSequence_GetMetaObjectFunction(void) {
    igAnimationSequence_GetMetaObject();
}

