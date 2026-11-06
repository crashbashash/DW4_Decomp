extern char igMetaField_GetPublishedMetaObject[];
extern char igUnsignedCharMetaField_GetVTable[];
extern char thunk_igUnsignedCharMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igUnsignedCharMetaField_callbackList[];
extern char igUnsignedCharMetaField_className[];
extern char g_igUnsignedCharMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igUnsignedCharMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedCharMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igUnsignedCharMetaField_GetMetaObject,
        igUnsignedCharMetaField_className,
        0x34, /* instance size */
        igUnsignedCharMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igUnsignedCharMetaField_callbackList /* callback list */
    );
}
