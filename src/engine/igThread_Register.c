extern char igNamedObject_GetPublishedMetaObject[];
extern char thunk_igThread_GetMetaObject[];
extern char igNamedObject_Register[];
extern char igThread_className[];
extern char g_igThread_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igThread_InitFields();

void igThread_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igThread_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igThread_GetMetaObject,
        igThread_className,
        0x30, /* instance size */
        0,
        &igThread_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
