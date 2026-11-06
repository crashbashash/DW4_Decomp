extern char igDependencyOrderedList_GetPublishedMetaObject[];
extern char igDependencyOrderedList_Register[];
extern char igEventReceiverOrderedList_GetVTable[];
extern char thunk_igEventReceiverOrderedList_GetMetaObject[];
extern char g_igEventReceiverOrderedList_callbackList[];
extern char igEventReceiverOrderedList_className[];
extern char g_igEventReceiverOrderedList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igEventReceiverOrderedList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventReceiverOrderedList_metaObject,
        igDependencyOrderedList_Register,
        igDependencyOrderedList_GetPublishedMetaObject,
        thunk_igEventReceiverOrderedList_GetMetaObject,
        igEventReceiverOrderedList_className,
        0x1C, /* instance size */
        igEventReceiverOrderedList_GetVTable,
        0,
        0, /* extra callback item */
        g_igEventReceiverOrderedList_callbackList /* callback list */
    );
}
