extern char igObject_GetMetaObject_ParentAccessor[];
extern char thunk_igCapabilityManager_GetMetaObject[];
extern char igObject_Register[];
extern char igCapabilityManager_className[];
extern char g_igCapabilityManager_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igCapabilityManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCapabilityManager_GetMetaObject,
        igCapabilityManager_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
