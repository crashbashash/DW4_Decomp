extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igBillboard_GetVTable[];
extern char thunk_igBillboard_GetMetaObject[];
extern char g_igBillboard_callbackList[];
extern char igBillboard_className[];
extern char g_igBillboard_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igBillboard_InitFields();

void igBillboard_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBillboard_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igBillboard_GetMetaObject,
        igBillboard_className,
        0x40, /* instance size */
        igBillboard_GetVTable,
        &igBillboard_InitFields,
        0, /* extra callback item */
        g_igBillboard_callbackList /* callback list */
    );
}
