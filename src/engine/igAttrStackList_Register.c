extern char igObjectList_GetPublishedMetaObject[];
extern char igAttrStackList_GetVTable[];
extern char thunk_igAttrStackList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igAttrStackList_callbackList[];
extern char igAttrStackList_className[];
extern char g_igAttrStackList_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igAttrStackList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrStackList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrStackList_GetMetaObject,
        igAttrStackList_className,
        0x14, /* instance size */
        igAttrStackList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrStackList_callbackList /* callback list */
    );
}
