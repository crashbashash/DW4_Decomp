extern char igDependencyOrderedList_GetPublishedMetaObject[];
extern char igDependencyOrderedList_Register[];
extern char igRendererOrderedList_GetVTable[];
extern char thunk_igRendererOrderedList_GetMetaObject[];
extern char g_igRendererOrderedList_callbackList[];
extern char igRendererOrderedList_className[];
extern char g_igRendererOrderedList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igRendererOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRendererOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igRendererOrderedList_GetMetaObject,
        igRendererOrderedList_className,
        0x1C, /* instance size */
        igRendererOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRendererOrderedList_callbackList /* callback list */
    );
}
