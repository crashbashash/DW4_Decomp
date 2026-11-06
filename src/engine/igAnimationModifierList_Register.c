extern char igObjectList_GetPublishedMetaObject[];
extern char igAnimationModifierList_GetVTable[];
extern char thunk_igAnimationModifierList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAnimationModifierList_callbackList[];
extern char igAnimationModifierList_className[];
extern char g_igAnimationModifierList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAnimationModifierList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimationModifierList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAnimationModifierList_GetMetaObject,
        igAnimationModifierList_className,
        0x14, /* instance size */
        igAnimationModifierList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAnimationModifierList_callbackList /* callback list */
    );
}
