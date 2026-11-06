extern char igPsx2AudioSourceList_GetVTable[];
extern char thunk_igPsx2AudioSourceList_GetMetaObject[];
extern char igDataList_GetPublishedMetaObject[];
extern char igDataList_Register[];
extern char igPsx2AudioSourceList_className[];
extern char g_igPsx2AudioSourceList_metaObject[];
int AudioLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igPsx2AudioSourceList_Register(void) {
    AudioLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2AudioSourceList_metaObject,
        igDataList_Register,
        igDataList_GetPublishedMetaObject,
        thunk_igPsx2AudioSourceList_GetMetaObject,
        igPsx2AudioSourceList_className,
        0x14, /* instance size */
        igPsx2AudioSourceList_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
