igMetaObject *igAnimationSequence_GetMetaObject(void)
{
    igMetaObject *g = g_igAnimationSequence_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a7080();
    return g_igAnimationSequence_metaObject[0];
}

void FUN_001a7080(void)
{
    igMetaObject_RunStaticInit(igAnimationSequence_Register);
}

void igAnimationSequence_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igAnimationSequence_metaObject),
        igTransformSource_Register,
        igTransformSource_GetPublishedMetaObject,
        thunk_igAnimationSequence_GetMetaObject,
        igAnimationSequence_className,
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

