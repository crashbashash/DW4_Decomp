extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igTransformSource_GetMetaObject[];
extern char igObject_Register[];
extern char igTransformSource_className[];
extern char g_igTransformSource_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igTransformSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igTransformSource_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igTransformSource_GetMetaObject,
        igTransformSource_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
