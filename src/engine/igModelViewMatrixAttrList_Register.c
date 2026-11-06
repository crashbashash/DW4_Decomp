extern char igObjectList_GetPublishedMetaObject[];
extern char igModelViewMatrixAttrList_GetVTable[];
extern char thunk_igModelViewMatrixAttrList_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igModelViewMatrixAttrList_callbackList[];
extern char igModelViewMatrixAttrList_className[];
extern char g_igModelViewMatrixAttrList_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igModelViewMatrixAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igModelViewMatrixAttrList_GetMetaObject,
        igModelViewMatrixAttrList_className,
        0x14, /* instance size */
        igModelViewMatrixAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixAttrList_callbackList /* callback list */
    );
}
