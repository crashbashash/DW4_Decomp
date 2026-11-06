extern char igVolume_Register[];
extern char igVolume_GetPublishedMetaObject[];
extern char igPlane_GetVTable[];
extern char thunk_igPlane_GetMetaObject[];
extern char thunk_FUN_0018c660[];
extern char igPlane_className[];
extern char g_igPlane_metaObject[];
int FUN_00186a40();
int igMetaObject_RegisterClass();
int igPlane_InitFields();

void igPlane_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPlane_metaObject,
        igVolume_Register,
        igVolume_GetPublishedMetaObject,
        thunk_igPlane_GetMetaObject,
        igPlane_className,
        0x1C, /* instance size */
        igPlane_GetVTable,
        &igPlane_InitFields,
        thunk_FUN_0018c660, /* extra callback item */
        0 /* callback list */
    );
}
