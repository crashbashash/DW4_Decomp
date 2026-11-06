extern char igMetaField_GetPublishedMetaObject[];
extern char igUnsignedShortMetaField_GetVTable[];
extern char thunk_igUnsignedShortMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedShortMetaField_callbackList[];
extern char igUnsignedShortMetaField_className[];
extern char g_igUnsignedShortMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igUnsignedShortMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedShortMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igUnsignedShortMetaField_GetMetaObject,
        igUnsignedShortMetaField_className,
        0x34, /* instance size */
        igUnsignedShortMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedShortMetaField_callbackList /* callback list */
    );
}
