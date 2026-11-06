extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationTransitionDefinition_GetVTable[];
extern char thunk_igAnimationTransitionDefinition_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationTransitionDefinition_callbackList[];
extern char igAnimationTransitionDefinition_className[];
extern char g_igAnimationTransitionDefinition_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationTransitionDefinition_InitFields();

void igAnimationTransitionDefinition_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationTransitionDefinition_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationTransitionDefinition_GetMetaObject,
        igAnimationTransitionDefinition_className,
        0x14, /* instance size */
        igAnimationTransitionDefinition_GetVTable,
        &igAnimationTransitionDefinition_InitFields,
        0, /* extra callback item */
        g_igAnimationTransitionDefinition_callbackList /* callback list */
    );
}
