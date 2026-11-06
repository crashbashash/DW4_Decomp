extern char igMetaField_GetPublishedMetaObject[];
extern char igUnsignedLongMetaField_GetVTable[];
extern char thunk_igUnsignedLongMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedLongMetaField_callbackList[];
extern char igUnsignedLongMetaField_className[];
extern char g_igUnsignedLongMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igUnsignedLongMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedLongMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igUnsignedLongMetaField_GetMetaObject,
        igUnsignedLongMetaField_className,
        0x34, /* instance size */
        igUnsignedLongMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedLongMetaField_callbackList /* callback list */
    );
}
