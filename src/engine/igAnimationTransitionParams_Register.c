extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationTransitionParams_GetVTable[];
extern char thunk_igAnimationTransitionParams_GetMetaObject[];
extern char igObject_Register[];
extern char igAnimationTransitionParams_className[];
extern char g_igAnimationTransitionParams_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationTransitionParams_InitFields();

void igAnimationTransitionParams_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationTransitionParams_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionParams_GetMetaObject,
        igAnimationTransitionParams_className,
        0x20, /* instance size */
        igAnimationTransitionParams_GetVTable,
        &igAnimationTransitionParams_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
