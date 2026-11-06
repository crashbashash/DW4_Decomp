extern char igContext_GetPublishedMetaObject[];
extern char thunk_igContextExt_GetMetaObject[];
extern char igContext_Register[];
extern char igContextExt_className[];
extern char g_igContextExt_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igContextExt_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igContextExt_metaObject,
        igContext_Register,
        igContext_GetPublishedMetaObject,
        thunk_igContextExt_GetMetaObject,
        igContextExt_className,
        0x14, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
