extern char igControllerManager_Register[];
extern char thunk_igPsx2ControllerManager_GetMetaObject[];
extern char igPsx2ControllerManager_GetVTable[];
extern char igControllerManager_GetPublishedMetaObject[];
extern char igPsx2ControllerManager_className[];
extern char g_igPsx2ControllerManager_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPsx2ControllerManager_InitFields();

void igPsx2ControllerManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ControllerManager_metaObject,
        igControllerManager_Register,
        igControllerManager_GetPublishedMetaObject,
        thunk_igPsx2ControllerManager_GetMetaObject,
        igPsx2ControllerManager_className,
        0x14, /* instance size */
        igPsx2ControllerManager_GetVTable,
        &igPsx2ControllerManager_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
