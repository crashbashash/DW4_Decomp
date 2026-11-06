extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationTransitionPoint_GetVTable[];
extern char thunk_igAnimationTransitionPoint_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationTransitionPoint_callbackList[];
extern char igAnimationTransitionPoint_className[];
extern char g_igAnimationTransitionPoint_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationTransitionPoint_InitFields();

void igAnimationTransitionPoint_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationTransitionPoint_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionPoint_GetMetaObject,
        igAnimationTransitionPoint_className,
        0x18, /* instance size */
        igAnimationTransitionPoint_GetVTable,
        &igAnimationTransitionPoint_InitFields,
        0, /* extra callback item */
        g_igAnimationTransitionPoint_callbackList /* callback list */
    );
}
