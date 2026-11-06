extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igDirectory_GetVTable[];
extern char thunk_igDirectory_GetMetaObject[];
extern char g_igDirectory_callbackList[];
extern char igDirectory_className[];
extern char g_igDirectory_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int thunk_FUN_002d7b00[4];
int igDirectory_InitFields();

void igDirectory_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igDirectory_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igDirectory_GetMetaObject,
        igDirectory_className,
        0x48, /* instance size */
        igDirectory_GetVTable,
        &igDirectory_InitFields,
        thunk_FUN_002d7b00, /* extra callback item */
        g_igDirectory_callbackList /* callback list */
    );
}
