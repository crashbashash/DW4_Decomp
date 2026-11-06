extern char igMetaField_GetPublishedMetaObject[];
extern char thunk_igRefMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igRefMetaField_callbackList[];
extern char igRefMetaField_className[];
extern char g_igRefMetaField_metaObject[];
int igMetaObject_RegisterClass();
int igRefMetaField_InitFields();

void igRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igRefMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igRefMetaField_GetMetaObject,
        igRefMetaField_className,
        0x38, /* instance size */
        0,
        &igRefMetaField_InitFields,
        0, /* extra callback item */
        g_igRefMetaField_callbackList /* callback list */
    );
}
