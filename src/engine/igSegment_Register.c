extern char igGroup_GetPublishedMetaObject[];
extern char igSegment_GetVTable[];
extern char thunk_igSegment_GetMetaObject[];
extern char igGroup_Register[];
extern char igSegment_className[];
extern char g_igSegment_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igSegment_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSegment_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igSegment_GetMetaObject,
        igSegment_className,
        0x20, /* instance size */
        igSegment_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
