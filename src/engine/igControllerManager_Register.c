extern char igEventProducer_GetPublishedMetaObject[];
extern char igEventProducer_Register[];
extern char thunk_igControllerManager_GetMetaObject[];
extern char g_igControllerManager_callbackList[];
extern char igControllerManager_className[];
extern char g_igControllerManager_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igControllerManager_InitFields();

void igControllerManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igControllerManager_metaObject,
        igEventProducer_Register,
        igEventProducer_GetPublishedMetaObject,
        thunk_igControllerManager_GetMetaObject,
        igControllerManager_className,
        0xC, /* instance size */
        0,
        &igControllerManager_InitFields,
        0, /* extra callback item */
        g_igControllerManager_callbackList /* callback list */
    );
}
