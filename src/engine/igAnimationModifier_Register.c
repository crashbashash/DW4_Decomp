extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationModifier_GetVTable[];
extern char thunk_igAnimationModifier_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationModifier_callbackList[];
extern char igAnimationModifier_className[];
extern char g_igAnimationModifier_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationModifier_InitFields();

void igAnimationModifier_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationModifier_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationModifier_GetMetaObject,
        igAnimationModifier_className,
        0x14, /* instance size */
        igAnimationModifier_GetVTable,
        &igAnimationModifier_InitFields,
        0, /* extra callback item */
        g_igAnimationModifier_callbackList /* callback list */
    );
}
