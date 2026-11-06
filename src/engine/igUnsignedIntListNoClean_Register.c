extern char igUnsignedIntList_GetPublishedMetaObject[];
extern char igUnsignedIntListNoClean_GetVTable[];
extern char thunk_igUnsignedIntListNoClean_GetMetaObject[];
extern char igUnsignedIntList_Register[];
extern char igUnsignedIntListNoClean_className[];
extern char g_igUnsignedIntListNoClean_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igUnsignedIntListNoClean_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igUnsignedIntListNoClean_metaObject,
        igUnsignedIntList_Register,
        igUnsignedIntList_GetPublishedMetaObject,
        thunk_igUnsignedIntListNoClean_GetMetaObject,
        igUnsignedIntListNoClean_className,
        0x14, /* instance size */
        igUnsignedIntListNoClean_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
