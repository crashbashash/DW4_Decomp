extern char igBase_GetPublishedMetaObject[];
extern char thunk_igItemBase_GetMetaObject[];
extern char igBase_Register[];
extern char igItemBase_className[];
extern char g_igItemBase_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igItemBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igItemBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igItemBase_GetMetaObject,
        igItemBase_className,
        0x20, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
