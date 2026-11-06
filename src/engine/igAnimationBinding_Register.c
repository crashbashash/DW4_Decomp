extern char igObject_GetMetaObject_ParentAccessor[];
extern char igAnimationBinding_GetVTable[];
extern char thunk_igAnimationBinding_GetMetaObject[];
extern char igObject_Register[];
extern char g_igAnimationBinding_callbackList[];
extern char igAnimationBinding_className[];
extern char g_igAnimationBinding_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimationBinding_InitFields();

void igAnimationBinding_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationBinding_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igAnimationBinding_GetMetaObject,
        igAnimationBinding_className,
        0x1C, /* instance size */
        igAnimationBinding_GetVTable,
        &igAnimationBinding_InitFields,
        0, /* extra callback item */
        g_igAnimationBinding_callbackList /* callback list */
    );
}
