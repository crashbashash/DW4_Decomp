extern char igObject_GetMetaObject_ParentAccessor[];
extern char igGraphPath_GetVTable[];
extern char thunk_igGraphPath_GetMetaObject[];
extern char igObject_Register[];
extern char g_igGraphPath_callbackList[];
extern char igGraphPath_className[];
extern char g_igGraphPath_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igGraphPath_InitFields();

void igGraphPath_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGraphPath_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igGraphPath_GetMetaObject,
        igGraphPath_className,
        0x1C, /* instance size */
        igGraphPath_GetVTable,
        &igGraphPath_InitFields,
        0, /* extra callback item */
        g_igGraphPath_callbackList /* callback list */
    );
}
