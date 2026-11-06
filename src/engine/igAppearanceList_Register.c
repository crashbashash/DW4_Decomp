extern char igObjectList_GetPublishedMetaObject[];
extern char igAppearanceList_GetVTable[];
extern char thunk_igAppearanceList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAppearanceList_callbackList[];
extern char igAppearanceList_className[];
extern char g_igAppearanceList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAppearanceList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAppearanceList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAppearanceList_GetMetaObject,
        igAppearanceList_className,
        0x14, /* instance size */
        igAppearanceList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAppearanceList_callbackList /* callback list */
    );
}
