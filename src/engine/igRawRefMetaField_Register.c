extern char igRefMetaField_GetPublishedMetaObject[];
extern char igRefMetaField_Register[];
extern char igRawRefMetaField_GetVTable[];
extern char thunk_igRawRefMetaField_GetMetaObject[];
extern char g_igRawRefMetaField_callbackList[];
extern char igRawRefMetaField_className[];
extern char g_igRawRefMetaField_metaObject[];
int igMetaObject_RegisterClass();

void igRawRefMetaField_Register(void) {
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRawRefMetaField_metaObject,
        igRefMetaField_Register,
        igRefMetaField_GetPublishedMetaObject,
        thunk_igRawRefMetaField_GetMetaObject,
        igRawRefMetaField_className,
        0x38, /* instance size */
        igRawRefMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igRawRefMetaField_callbackList /* callback list */
    );
}
