extern char igBase_GetPublishedMetaObject[];
extern char igMessageBase_GetVTable[];
extern char thunk_igMessageBase_GetMetaObject[];
extern char igBase_Register[];
extern char igMessageBase_className[];
extern char g_igMessageBase_metaObject[];
int BaseLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igMessageBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMessageBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igMessageBase_GetMetaObject,
        igMessageBase_className,
        0x20, /* instance size */
        igMessageBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
