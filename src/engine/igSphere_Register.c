extern char igVolume_Register[];
extern char igSphere_GetVTable[];
extern char thunk_igSphere_GetMetaObject[];
extern char igVolume_GetPublishedMetaObject[];
extern char thunk_FUN_0018d480[];
extern char igSphere_className[];
extern char g_igSphere_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igSphere_InitFields();

void igSphere_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igSphere_metaObject,
        igVolume_Register,
        igVolume_GetPublishedMetaObject,
        thunk_igSphere_GetMetaObject,
        igSphere_className,
        0x18, /* instance size */
        igSphere_GetVTable,
        &igSphere_InitFields,
        thunk_FUN_0018d480, /* extra callback item */
        0 /* callback list */
    );
}
