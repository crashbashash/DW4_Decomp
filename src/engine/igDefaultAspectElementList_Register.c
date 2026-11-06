extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igDefaultAspectElementList_GetVTable[];
extern char thunk_igDefaultAspectElementList_GetMetaObject[];
extern char g_igDefaultAspectElementList_callbackList[];
extern char igDefaultAspectElementList_className[];
extern char g_igDefaultAspectElementList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igDefaultAspectElementList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDefaultAspectElementList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDefaultAspectElementList_GetMetaObject,
        igDefaultAspectElementList_className,
        0x14, /* instance size */
        igDefaultAspectElementList_GetVTable,
        0,
        0, /* extra callback item */
        g_igDefaultAspectElementList_callbackList /* callback list */
    );
}
