extern char thunk_igWindow_GetMetaObject[];
extern char igEventProducer_GetPublishedMetaObject[];
extern char igEventProducer_Register[];
extern char igWindow_className[];
extern char g_igWindow_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
void FUN_00145e80(void);
void igWindow_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igWindow_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igWindow_GetMetaObject,
        igWindow_className,
        8, /* instance size */
        0,
        FUN_00145e80,
        0, /* extra callback item */
        0 /* callback list */
    );
}
