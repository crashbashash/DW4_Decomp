extern char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern char igNonRefCountedObjectList_Register[];
extern char igNonRefCountedViewList_GetVTable[];
extern char thunk_igNonRefCountedViewList_GetMetaObject[];
extern char g_igNonRefCountedViewList_callbackList[];
extern char igNonRefCountedViewList_className[];
extern char g_igNonRefCountedViewList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igNonRefCountedViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedViewList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedViewList_GetMetaObject,
        igNonRefCountedViewList_className,
        0x14, /* instance size */
        igNonRefCountedViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedViewList_callbackList /* callback list */
    );
}
