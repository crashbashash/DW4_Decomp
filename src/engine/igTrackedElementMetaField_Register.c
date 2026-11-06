extern char igTrackedElementMetaField_GetVTable[];
extern char thunk_igTrackedElementMetaField_GetMetaObject[];
extern char igCompoundMetaField_GetPublishedMetaObject[];
extern char igCompoundMetaField_Register[];
extern char g_igTrackedElementMetaField_callbackList[];
extern char igTrackedElementMetaField_className[];
extern char g_igTrackedElementMetaField_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igTrackedElementMetaField_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTrackedElementMetaField_metaObject,
        igCompoundMetaField_Register,
        igCompoundMetaField_GetPublishedMetaObject,
        thunk_igTrackedElementMetaField_GetMetaObject,
        igTrackedElementMetaField_className,
        0x38, /* instance size */
        igTrackedElementMetaField_GetVTable,
        0,
        0, /* extra callback item */
        g_igTrackedElementMetaField_callbackList /* callback list */
    );
}
