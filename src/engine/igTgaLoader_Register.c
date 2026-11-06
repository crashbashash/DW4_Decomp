extern char igImageLoader_Register[];
extern char igTgaLoader_GetVTable[];
extern char thunk_igTgaLoader_GetMetaObject[];
extern char igImageLoader_GetPublishedMetaObject[];
extern char g_igTgaLoader_callbackList[];
extern char igTgaLoader_className[];
extern char g_igTgaLoader_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();
int igTgaLoader_InitFields();

void igTgaLoader_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igTgaLoader_metaObject,
        igImageLoader_Register,
        igImageLoader_GetPublishedMetaObject,
        thunk_igTgaLoader_GetMetaObject,
        igTgaLoader_className,
        0x30, /* instance size */
        igTgaLoader_GetVTable,
        &igTgaLoader_InitFields,
        0, /* extra callback item */
        g_igTgaLoader_callbackList /* callback list */
    );
}
