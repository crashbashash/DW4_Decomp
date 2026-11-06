extern char igController_Register[];
extern char thunk_igPsx2Controller_GetMetaObject[];
extern char igPsx2Controller_GetVTable[];
extern char igController_GetPublishedMetaObject[];
extern char g_igPsx2Controller_callbackList[];
extern char igPsx2Controller_className[];
extern char g_igPsx2Controller_metaObject[];
int WindowInputLibrary_MarkRegistered();
int igMetaObject_RegisterClass();
int igPsx2Controller_InitFields();

void igPsx2Controller_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Controller_metaObject,
        igController_Register,
        igController_GetPublishedMetaObject,
        thunk_igPsx2Controller_GetMetaObject,
        igPsx2Controller_className,
        0x70, /* instance size */
        igPsx2Controller_GetVTable,
        &igPsx2Controller_InitFields,
        0, /* extra callback item */
        g_igPsx2Controller_callbackList /* callback list */
    );
}
