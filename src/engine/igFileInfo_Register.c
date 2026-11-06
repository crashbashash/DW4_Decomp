extern char igNamedObject_GetPublishedMetaObject[];
extern char igFileInfo_GetVTable[];
extern char thunk_igFileInfo_GetMetaObject[];
extern char igNamedObject_Register[];
extern char g_igFileInfo_callbackList[];
extern char igFileInfo_className[];
extern char g_igFileInfo_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igFileInfo_InitFields();

void igFileInfo_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileInfo_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igFileInfo_GetMetaObject,
        igFileInfo_className,
        0x1C, /* instance size */
        igFileInfo_GetVTable,
        &igFileInfo_InitFields,
        0, /* extra callback item */
        g_igFileInfo_callbackList /* callback list */
    );
}
