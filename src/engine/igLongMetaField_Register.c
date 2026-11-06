extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igLongMetaField_GetVTable[];
extern char thunk_igLongMetaField_GetMetaObject[];
extern char g_igLongMetaField_callbackList[];
extern char igLongMetaField_className[];
extern char g_igLongMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igLongMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLongMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igLongMetaField_GetMetaObject,
        igLongMetaField_className,
        0x34, /* instance size */
        igLongMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igLongMetaField_callbackList /* callback list */
    );
}
