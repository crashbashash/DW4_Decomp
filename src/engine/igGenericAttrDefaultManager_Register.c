extern char igAttrDefaultManager_GetPublishedMetaObject[];
extern char igGenericAttrDefaultManager_GetVTable[];
extern char thunk_igGenericAttrDefaultManager_GetMetaObject[];
extern char igAttrDefaultManager_Register[];
extern char igGenericAttrDefaultManager_className[];
extern char g_igGenericAttrDefaultManager_metaObject[];
int AttrsLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igGenericAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGenericAttrDefaultManager_metaObject,
        igAttrDefaultManager_Register,
        igAttrDefaultManager_GetPublishedMetaObject,
        thunk_igGenericAttrDefaultManager_GetMetaObject,
        igGenericAttrDefaultManager_className,
        8, /* instance size */
        igGenericAttrDefaultManager_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
