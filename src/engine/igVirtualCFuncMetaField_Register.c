extern char igMetaField_GetPublishedMetaObject[];
extern char igVirtualCFuncMetaField_GetVTable[];
extern char thunk_igVirtualCFuncMetaField_GetMetaObject[];
extern char igMetaField_Register[];
extern char g_igVirtualCFuncMetaField_callbackList[];
extern char igVirtualCFuncMetaField_className[];
extern char g_igVirtualCFuncMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igVirtualCFuncMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igVirtualCFuncMetaField_metaObject,
        igMetaField_Register,
        igMetaField_GetPublishedMetaObject,
        thunk_igVirtualCFuncMetaField_GetMetaObject,
        igVirtualCFuncMetaField_className,
        0x34, /* instance size */
        igVirtualCFuncMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igVirtualCFuncMetaField_callbackList /* callback list */
    );
}
