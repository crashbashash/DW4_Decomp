extern char igObjectList_GetPublishedMetaObject[];
extern char igVertexDataList_GetVTable[];
extern char thunk_igVertexDataList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igVertexDataList_callbackList[];
extern char igVertexDataList_className[];
extern char g_igVertexDataList_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igVertexDataList_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVertexDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igVertexDataList_GetMetaObject,
        igVertexDataList_className,
        0x14, /* instance size */
        igVertexDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_igVertexDataList_callbackList /* callback list */
    );
}
