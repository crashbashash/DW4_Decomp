extern char igGroup_GetPublishedMetaObject[];
extern char igModelViewMatrixBoneSelect_GetVTable[];
extern char thunk_igModelViewMatrixBoneSelect_GetMetaObject[];
extern char igGroup_Register[];
extern char igModelViewMatrixBoneSelect_className[];
extern char g_igModelViewMatrixBoneSelect_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igModelViewMatrixBoneSelect_InitFields();

void igModelViewMatrixBoneSelect_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igModelViewMatrixBoneSelect_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igModelViewMatrixBoneSelect_GetMetaObject,
        igModelViewMatrixBoneSelect_className,
        0x24, /* instance size */
        igModelViewMatrixBoneSelect_GetVTable,
        &igModelViewMatrixBoneSelect_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
