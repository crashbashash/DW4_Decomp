extern char igObjectList_GetPublishedMetaObject[];
extern char igAttrList_GetVTable[];
extern char thunk_igAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAttrList_callbackList[];
extern char igAttrList_className[];
extern char g_igAttrList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrList_GetMetaObject,
        igAttrList_className,
        0x14, /* instance size */
        igAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrList_callbackList /* callback list */
    );
}
