extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igAnimationHierarchy_GetMetaObject[];
extern char igNamedObject_Register[];
extern char igAnimationHierarchy_className[];
extern char g_igAnimationHierarchy_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationHierarchy_InitFields();

void igAnimationHierarchy_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igAnimationHierarchy_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimationHierarchy_GetMetaObject,
        igAnimationHierarchy_className,
        0x10, /* instance size */
        0,
        &igAnimationHierarchy_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
