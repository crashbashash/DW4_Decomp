extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igHotKeyBindingList_GetVTable[];
extern char thunk_igHotKeyBindingList_GetMetaObject[];
extern char g_igHotKeyBindingList_callbackList[];
extern char igHotKeyBindingList_className[];
extern char g_igHotKeyBindingList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igHotKeyBindingList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igHotKeyBindingList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igHotKeyBindingList_GetMetaObject,
        igHotKeyBindingList_className,
        0x14, /* instance size */
        igHotKeyBindingList_GetVTable,
        0,
        0, /* extra callback item */
        g_igHotKeyBindingList_callbackList /* callback list */
    );
}
