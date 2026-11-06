extern char igObjectList_GetPublishedMetaObject[];
extern char igAttrListList_GetVTable[];
extern char thunk_igAttrListList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAttrListList_callbackList[];
extern char igAttrListList_className[];
extern char g_igAttrListList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAttrListList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrListList_GetMetaObject,
        igAttrListList_className,
        0x14, /* instance size */
        igAttrListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrListList_callbackList /* callback list */
    );
}
