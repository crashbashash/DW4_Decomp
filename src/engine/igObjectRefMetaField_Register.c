extern char igRefMetaField_GetPublishedMetaObject[];
extern char igRefMetaField_Register[];
extern char igObjectRefMetaField_GetVTable[];
extern char thunk_igObjectRefMetaField_GetMetaObject[];
extern char g_igObjectRefMetaField_callbackList[];
extern char igObjectRefMetaField_className[];
extern char g_igObjectRefMetaField_metaObject[];
int igMetaObject_RegisterClass();
int igObjectRefMetaField_InitFields();

void igObjectRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObjectRefMetaField_metaObject,
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        thunk_igObjectRefMetaField_GetMetaObject,
        igObjectRefMetaField_className,
        0x44, /* instance size */
        igObjectRefMetaField_GetVTable,
        &igObjectRefMetaField_InitFields,
        0, /* extra callback item */
        g_igObjectRefMetaField_callbackList /* callback list */
    );
}
