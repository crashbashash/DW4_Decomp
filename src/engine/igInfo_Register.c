extern char igNamedObject_GetPublishedMetaObject[];
extern char igNamedObject_Register[];
extern char igInfo_GetVTable[];
extern char thunk_igInfo_GetMetaObject[];
extern char g_igInfo_callbackList[];
extern char igInfo_className[];
extern char g_igInfo_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igInfo_InitFields();

void igInfo_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igInfo_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igInfo_GetMetaObject,
        igInfo_className,
        0x14, /* instance size */
        igInfo_GetVTable,
        &igInfo_InitFields,
        0, /* extra callback item */
        g_igInfo_callbackList /* callback list */
    );
}
