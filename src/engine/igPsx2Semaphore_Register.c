extern char igSemaphore_Register[];
extern char thunk_igPsx2Semaphore_GetMetaObject[];
extern char igPsx2Semaphore_GetVTable[];
extern char igSemaphore_GetPublishedMetaObject[];
extern char igPsx2Semaphore_className[];
extern char g_igPsx2Semaphore_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
int igPsx2Semaphore_InitFields();

void igPsx2Semaphore_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Semaphore_metaObject,
        igSemaphore_Register,
        igSemaphore_GetPublishedMetaObject,
        thunk_igPsx2Semaphore_GetMetaObject,
        igPsx2Semaphore_className,
        0x18, /* instance size */
        igPsx2Semaphore_GetVTable,
        &igPsx2Semaphore_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
