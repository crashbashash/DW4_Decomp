extern char igGroup_GetPublishedMetaObject[];
extern char igSwitch_GetVTable[];
extern char thunk_igSwitch_GetMetaObject[];
extern char igGroup_Register[];
extern char g_igSwitch_callbackList[];
extern char igSwitch_className[];
extern char g_igSwitch_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igSwitch_InitFields();

void igSwitch_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSwitch_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igSwitch_GetMetaObject,
        igSwitch_className,
        0x24, /* instance size */
        igSwitch_GetVTable,
        &igSwitch_InitFields,
        0, /* extra callback item */
        g_igSwitch_callbackList /* callback list */
    );
}
