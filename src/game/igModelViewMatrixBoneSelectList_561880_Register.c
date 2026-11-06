extern char igObjectList_GetPublishedMetaObject[];
extern char igModelViewMatrixBoneSelectList_561880_GetVTable[];
extern char thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject[];
extern char igObjectList_Register[];
extern char g_igModelViewMatrixBoneSelectList_561880_callbackList[];
extern char igModelViewMatrixBoneSelectList_className[];
extern char g_igModelViewMatrixBoneSelectList_metaObject_00561880[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igModelViewMatrixBoneSelectList_561880_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixBoneSelectList_metaObject_00561880,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject,
        igModelViewMatrixBoneSelectList_className,
        0x14, /* instance size */
        igModelViewMatrixBoneSelectList_561880_GetVTable,
        0,
        0, /* extra callback item */
        g_igModelViewMatrixBoneSelectList_561880_callbackList /* callback list */
    );
}
