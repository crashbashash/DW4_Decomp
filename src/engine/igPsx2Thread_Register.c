extern char igThread_Register[];
extern char thunk_igPsx2Thread_GetMetaObject[];
extern char igPsx2Thread_GetVTable[];
extern char igThread_GetPublishedMetaObject[];
extern char g_igPsx2Thread_callbackList[];
extern char igPsx2Thread_className[];
extern char g_igPsx2Thread_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2Thread_InitFields();

void igPsx2Thread_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Thread_metaObject,
        igThread_Register,
        igThread_GetPublishedMetaObject,
        thunk_igPsx2Thread_GetMetaObject,
        igPsx2Thread_className,
        0x40, /* instance size */
        igPsx2Thread_GetVTable,
        &igPsx2Thread_InitFields,
        0, /* extra callback item */
        g_igPsx2Thread_callbackList /* callback list */
    );
}
