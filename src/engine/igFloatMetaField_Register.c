extern char igMetaField_GetPublishedMetaObject[];
extern char igMetaField_Register[];
extern char igFloatMetaField_GetVTable[];
extern char thunk_igFloatMetaField_GetMetaObject[];
extern char g_igFloatMetaField_callbackList[];
extern char igFloatMetaField_className[];
extern char g_igFloatMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igFloatMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFloatMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igFloatMetaField_GetMetaObject,
        igFloatMetaField_className,
        0x34, /* instance size */
        igFloatMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igFloatMetaField_callbackList /* callback list */
    );
}
