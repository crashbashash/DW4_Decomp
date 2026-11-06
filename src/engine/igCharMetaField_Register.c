extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igCharMetaField_GetVTable[];
extern char thunk_igCharMetaField_GetMetaObject[];
extern char g_igCharMetaField_callbackList[];
extern char igCharMetaField_className[];
extern char g_igCharMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igCharMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igCharMetaField_GetMetaObject,
        igCharMetaField_className,
        0x34, /* instance size */
        igCharMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igCharMetaField_callbackList /* callback list */
    );
}
