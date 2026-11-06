extern char igCharListNoClean_GetVTable[];
extern char thunk_igCharListNoClean_GetMetaObject[];
extern char igCharList_GetPublishedMetaObject[];
extern char igCharList_Register[];
extern char igCharListNoClean_className[];
extern char g_igCharListNoClean_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igCharListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCharListNoClean_metaObject,
        igCharList_Register,
        igCharList_GetPublishedMetaObject,
        thunk_igCharListNoClean_GetMetaObject,
        igCharListNoClean_className,
        0x14, /* instance size */
        igCharListNoClean_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
