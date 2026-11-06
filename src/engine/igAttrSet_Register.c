extern char igGroup_GetPublishedMetaObject[];
extern char igGroup_Register[];
extern char igAttrSet_GetVTable[];
extern char thunk_igAttrSet_GetMetaObject[];
extern char g_igAttrSet_callbackList[];
extern char igAttrSet_className[];
extern char g_igAttrSet_metaObject[];
int SceneGraphLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igAttrSet_InitFields();

void igAttrSet_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrSet_metaObject,
        igGroup_Register,
        igGroup_GetPublishedMetaObject,
        thunk_igAttrSet_GetMetaObject,
        igAttrSet_className,
        0x28, /* instance size */
        igAttrSet_GetVTable,
        &igAttrSet_InitFields,
        0, /* extra callback item */
        g_igAttrSet_callbackList /* callback list */
    );
}
