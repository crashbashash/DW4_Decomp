extern char igStringMetaField_GetVTable[];
extern char thunk_igStringMetaField_GetMetaObject[];
extern char igRefMetaField_GetPublishedMetaObject[];
extern char igRefMetaField_Register[];
extern char g_igStringMetaField_callbackList[];
extern char igStringMetaField_className[];
extern char g_igStringMetaField_metaObject[];
int igMetaObject_RegisterClass();
int igStringMetaField_InitFields();

void igStringMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igStringMetaField_metaObject,
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        thunk_igStringMetaField_GetMetaObject,
        igStringMetaField_className,
        0x3C, /* instance size */
        igStringMetaField_GetVTable,
        &igStringMetaField_InitFields,
        0, /* extra callback item */
        g_igStringMetaField_callbackList /* callback list */
    );
}
