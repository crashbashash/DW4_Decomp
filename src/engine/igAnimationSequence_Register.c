extern char igTransformSource_Register[];
extern char igTransformSource_GetPublishedMetaObject[];
extern char thunk_igAnimationSequence_GetMetaObject[];
extern char igAnimationSequence_className[];
extern char g_igAnimationSequence_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationSequence_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAnimationSequence_metaObject,
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
