extern char igTransformSource_Register[];
extern char thunk_igTransformSequence_GetMetaObject[];
extern char igTransformSource_GetPublishedMetaObject[];
extern char g_igTransformSequence_callbackList[];
extern char igTransformSequence_className[];
extern char g_igTransformSequence_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igTransformSequence_InitFields();

void igTransformSequence_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igTransformSequence_metaObject,
        igTransformSource_Register,
        igTransformSource_GetPublishedMetaObject,
        thunk_igTransformSequence_GetMetaObject,
        igTransformSequence_className,
        0x38, /* instance size */
        0,
        &igTransformSequence_InitFields,
        0, /* extra callback item */
        g_igTransformSequence_callbackList /* callback list */
    );
}
