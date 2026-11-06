extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igDoubleMetaField_GetVTable[];
extern char thunk_igDoubleMetaField_GetMetaObject[];
extern char g_igDoubleMetaField_callbackList[];
extern char igDoubleMetaField_className[];
extern char g_igDoubleMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igDoubleMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDoubleMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igDoubleMetaField_GetMetaObject,
        igDoubleMetaField_className,
        0x34, /* instance size */
        igDoubleMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igDoubleMetaField_callbackList /* callback list */
    );
}
