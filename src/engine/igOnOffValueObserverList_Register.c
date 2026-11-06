extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igOnOffValueObserverList_GetVTable[];
extern char thunk_igOnOffValueObserverList_GetMetaObject[];
extern char g_igOnOffValueObserverList_callbackList[];
extern char igOnOffValueObserverList_className[];
extern char g_igOnOffValueObserverList_metaObject[];
int igMetaObject_RegisterClass();
int GuiLibrary_MarkRegistered();

void igOnOffValueObserverList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igOnOffValueObserverList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igOnOffValueObserverList_GetMetaObject,
        igOnOffValueObserverList_className,
        0x14, /* instance size */
        igOnOffValueObserverList_GetVTable,
        0,
        0, /* extra callback item */
        g_igOnOffValueObserverList_callbackList /* callback list */
    );
}
