extern char igMetaField_GetPublishedMetaObject[];
extern char igShortMetaField_GetVTable[];
extern char thunk_igShortMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igShortMetaField_callbackList[];
extern char igShortMetaField_className[];
extern char g_igShortMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igShortMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igShortMetaField_GetMetaObject,
        igShortMetaField_className,
        0x34, /* instance size */
        igShortMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igShortMetaField_callbackList /* callback list */
    );
}
