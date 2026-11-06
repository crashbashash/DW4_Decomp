extern char igObjectList_GetPublishedMetaObject[];
extern char igObjectList_Register[];
extern char igContextExtList_GetVTable[];
extern char thunk_igContextExtList_GetMetaObject[];
extern char g_igContextExtList_callbackList[];
extern char igContextExtList_className[];
extern char g_igContextExtList_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextExtList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igContextExtList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igContextExtList_GetMetaObject,
        igContextExtList_className,
        0x14, /* instance size */
        igContextExtList_GetVTable,
        0,
        0, /* extra callback item */
        g_igContextExtList_callbackList /* callback list */
    );
}
