extern char igMedia_Register[];
extern char thunk_igPsx2Media_GetMetaObject[];
extern char igPsx2Media_GetVTable[];
extern char igMedia_GetPublishedMetaObject[];
extern char g_igPsx2Media_callbackList[];
extern char igPsx2Media_className[];
extern char g_igPsx2Media_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2Media_InitFields();

void igPsx2Media_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Media_metaObject,
        igMedia_Register,
        igMedia_GetPublishedMetaObject,
        thunk_igPsx2Media_GetMetaObject,
        igPsx2Media_className,
        0x28, /* instance size */
        igPsx2Media_GetVTable,
        &igPsx2Media_InitFields,
        0, /* extra callback item */
        g_igPsx2Media_callbackList /* callback list */
    );
}
