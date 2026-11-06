extern char igNamedObject_GetPublishedMetaObject[];
extern char igAnimation_GetVTable[];
extern char thunk_igAnimation_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igAnimation_callbackList[];
extern char igAnimation_className[];
extern char g_igAnimation_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAnimation_InitFields();

void igAnimation_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAnimation_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igAnimation_GetMetaObject,
        igAnimation_className,
        0x40, /* instance size */
        igAnimation_GetVTable,
        &igAnimation_InitFields,
        0, /* extra callback item */
        g_igAnimation_callbackList /* callback list */
    );
}
