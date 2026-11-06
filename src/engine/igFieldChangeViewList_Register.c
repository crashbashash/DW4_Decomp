extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igFieldChangeViewList_GetVTable[];
extern char thunk_igFieldChangeViewList_GetMetaObject[];
extern char g_igFieldChangeViewList_callbackList[];
extern char igFieldChangeViewList_className[];
extern char g_igFieldChangeViewList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igFieldChangeViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFieldChangeViewList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igFieldChangeViewList_GetMetaObject,
        igFieldChangeViewList_className,
        0x14, /* instance size */
        igFieldChangeViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igFieldChangeViewList_callbackList /* callback list */
    );
}
