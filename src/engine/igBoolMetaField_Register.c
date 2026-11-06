extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igBoolMetaField_GetVTable[];
extern char thunk_igBoolMetaField_GetMetaObject[];
extern char g_igBoolMetaField_callbackList[];
extern char igBoolMetaField_className[];
extern char g_igBoolMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igBoolMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igBoolMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igBoolMetaField_GetMetaObject,
        igBoolMetaField_className,
        0x34, /* instance size */
        igBoolMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igBoolMetaField_callbackList /* callback list */
    );
}
