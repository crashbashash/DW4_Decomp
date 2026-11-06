extern char igVisualContextAttrDefaultManager_GetVTable[];
extern char thunk_igVisualContextAttrDefaultManager_GetMetaObject[];
extern char igAttrDefaultManager_GetPublishedMetaObject[];
extern char igAttrDefaultManager_Register[];
extern char g_igVisualContextAttrDefaultManager_callbackList[];
extern char igVisualContextAttrDefaultManager_className[];
extern char g_igVisualContextAttrDefaultManager_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igVisualContextAttrDefaultManager_InitFields();

void igVisualContextAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVisualContextAttrDefaultManager_metaObject,
        igAttrDefaultManager_Register,
        igAttrDefaultManager_GetPublishedMetaObject,
        thunk_igVisualContextAttrDefaultManager_GetMetaObject,
        igVisualContextAttrDefaultManager_className,
        0xC, /* instance size */
        igVisualContextAttrDefaultManager_GetVTable,
        &igVisualContextAttrDefaultManager_InitFields,
        0, /* extra callback item */
        g_igVisualContextAttrDefaultManager_callbackList /* callback list */
    );
}
