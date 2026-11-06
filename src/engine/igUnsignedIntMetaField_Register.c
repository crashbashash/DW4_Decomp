extern char igMetaField_GetPublishedMetaObject[];
extern char igUnsignedIntMetaField_GetVTable[];
extern char thunk_igUnsignedIntMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedIntMetaField_callbackList[];
extern char igUnsignedIntMetaField_className[];
extern char g_igUnsignedIntMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igUnsignedIntMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedIntMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igUnsignedIntMetaField_GetMetaObject,
        igUnsignedIntMetaField_className,
        0x34, /* instance size */
        igUnsignedIntMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedIntMetaField_callbackList /* callback list */
    );
}
