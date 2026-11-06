extern char igIntListNoClean_GetVTable[];
extern char thunk_igIntListNoClean_GetMetaObject[];
extern char igIntList_GetPublishedMetaObject[];
extern char igIntList_Register[];
extern char igIntListNoClean_className[];
extern char g_igIntListNoClean_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igIntListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igIntListNoClean_metaObject,
        igIntList_Register,
        igIntList_GetPublishedMetaObject,
        thunk_igIntListNoClean_GetMetaObject,
        igIntListNoClean_className,
        0x14, /* instance size */
        igIntListNoClean_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
