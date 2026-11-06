extern char igRenderer_GetPublishedMetaObject[];
extern char igFlushRenderer_GetVTable[];
extern char thunk_igFlushRenderer_GetMetaObject[];
extern char igRenderer_Register[];
extern char igFlushRenderer_className[];
extern char g_igFlushRenderer_metaObject[];
int InsightLibrary_MarkRegistered();
int igMetaObject_RegisterClass();

void igFlushRenderer_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFlushRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        thunk_igFlushRenderer_GetMetaObject,
        igFlushRenderer_className,
        0xC, /* instance size */
        igFlushRenderer_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
