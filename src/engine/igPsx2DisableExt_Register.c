extern char igDisableExt_Register[];
extern char thunk_igPsx2DisableExt_GetMetaObject[];
extern char igPsx2DisableExt_GetVTable[];
extern char igDisableExt_GetPublishedMetaObject[];
extern char g_igPsx2DisableExt_callbackList[];
extern char igPsx2DisableExt_className[];
extern char g_igPsx2DisableExt_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igPsx2DisableExt_InitFields();

void igPsx2DisableExt_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2DisableExt_metaObject,
        igDisableExt_Register,
        igDisableExt_GetPublishedMetaObject,
        thunk_igPsx2DisableExt_GetMetaObject,
        igPsx2DisableExt_className,
        0x18, /* instance size */
        igPsx2DisableExt_GetVTable,
        &igPsx2DisableExt_InitFields,
        0, /* extra callback item */
        g_igPsx2DisableExt_callbackList /* callback list */
    );
}
