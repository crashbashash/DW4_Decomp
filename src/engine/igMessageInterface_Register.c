extern char igInterface_GetPublishedMetaObject[];
extern char igMessageInterface_GetVTable[];
extern char thunk_igMessageInterface_GetMetaObject[];
extern char igInterface_Register[];
extern char g_igMessageInterface_callbackList[];
extern char igMessageInterface_className[];
extern char g_igMessageInterface_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igMessageInterface_InitFields();

void igMessageInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageInterface_metaObject,
        igInterface_Register,
        igInterface_GetPublishedMetaObject,
        thunk_igMessageInterface_GetMetaObject,
        igMessageInterface_className,
        0x24, /* instance size */
        igMessageInterface_GetVTable,
        &igMessageInterface_InitFields,
        0, /* extra callback item */
        g_igMessageInterface_callbackList /* callback list */
    );
}
