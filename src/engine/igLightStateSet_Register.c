extern char igGroup_GetPublishedMetaObject[];
extern char igLightStateSet_GetVTable[];
extern char thunk_igLightStateSet_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igLightStateSet_callbackList[];
extern char igLightStateSet_className[];
extern char g_igLightStateSet_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igLightStateSet_InitFields();

void igLightStateSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightStateSet_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igLightStateSet_GetMetaObject,
        igLightStateSet_className,
        0x24, /* instance size */
        igLightStateSet_GetVTable,
        &igLightStateSet_InitFields,
        0, /* extra callback item */
        g_igLightStateSet_callbackList /* callback list */
    );
}
