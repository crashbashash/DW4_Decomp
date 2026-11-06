extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igIntMetaField_GetVTable[];
extern char thunk_igIntMetaField_GetMetaObject[];
extern char g_igIntMetaField_callbackList[];
extern char igIntMetaField_className[];
extern char g_igIntMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igIntMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igIntMetaField_GetMetaObject,
        igIntMetaField_className,
        0x34, /* instance size */
        igIntMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igIntMetaField_callbackList /* callback list */
    );
}
