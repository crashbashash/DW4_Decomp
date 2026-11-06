extern char thunk_igImageLoader_GetMetaObject[];
extern char igImageUtils_GetPublishedMetaObject[];
extern char igImageUtils_Register[];
extern char igImageLoader_className[];
extern char g_igImageLoader_metaObject[];
int FUN_00149bc0();
int igMetaObject_RegisterClass();

void igImageLoader_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igImageLoader_metaObject,
        igImageUtils_Register,
        igImageUtils_GetPublishedMetaObject,
        thunk_igImageLoader_GetMetaObject,
        igImageLoader_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
