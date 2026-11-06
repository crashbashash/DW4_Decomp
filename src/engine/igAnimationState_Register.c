extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationState_GetVTable[];
extern char thunk_igAnimationState_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationState_callbackList[];
extern char igAnimationState_className[];
extern char g_igAnimationState_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationState_InitFields();

void igAnimationState_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationState_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationState_GetMetaObject,
        igAnimationState_className,
        0xA0, /* instance size */
        igAnimationState_GetVTable,
        &igAnimationState_InitFields,
        0, /* extra callback item */
        g_igAnimationState_callbackList /* callback list */
    );
}
