extern char igBitMask_GetVTable[];
extern char thunk_igBitMask_GetMetaObject[];
extern char igUnsignedIntList_GetPublishedMetaObject[];
extern char igUnsignedIntList_Register[];
extern char igBitMask_className[];
extern char g_igBitMask_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBitMask_InitFields();

void igBitMask_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBitMask_metaObject,
        igUnsignedIntList_Register,
        igUnsignedIntList_GetPublishedMetaObject,
        thunk_igBitMask_GetMetaObject,
        igBitMask_className,
        0x18, /* instance size */
        igBitMask_GetVTable,
        &igBitMask_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
