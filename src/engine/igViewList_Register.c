extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igViewList_GetVTable[];
extern char thunk_igViewList_GetMetaObject[];
extern char g_igViewList_callbackList[];
extern char igViewList_className[];
extern char g_igViewList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igViewList_GetMetaObject,
        igViewList_className,
        0x14, /* instance size */
        igViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igViewList_callbackList /* callback list */
    );
}
