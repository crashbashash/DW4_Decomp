extern char igEventProducer_GetPublishedMetaObject[];
extern char igEventProducer_Register[];
extern char thunk_igController_GetMetaObject[];
extern char igController_className[];
extern char g_igController_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igController_InitFields();

void igController_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igController_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igController_GetMetaObject,
        igController_className,
        0x10, /* instance size */
        0,
        &igController_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
