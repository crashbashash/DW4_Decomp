extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igDependencyMetaField_GetVTable[];
extern char thunk_igDependencyMetaField_GetMetaObject[];
extern char igCompoundMetaField_Register[];
extern char g_igDependencyMetaField_callbackList[];
extern char igDependencyMetaField_className[];
extern char g_igDependencyMetaField_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igDependencyMetaField_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDependencyMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igDependencyMetaField_GetMetaObject,
        igDependencyMetaField_className,
        0x38, /* instance size */
        igDependencyMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igDependencyMetaField_callbackList /* callback list */
    );
}
