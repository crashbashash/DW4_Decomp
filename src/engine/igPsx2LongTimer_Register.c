extern char igLongTimer_Register[];
extern char thunk_igPsx2LongTimer_GetMetaObject[];
extern char igPsx2LongTimer_GetVTable[];
extern char igLongTimer_GetPublishedMetaObject[];
void FUN_002cfe00(void);
extern char igPsx2LongTimer_className[];
extern char g_igPsx2LongTimer_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();

void igPsx2LongTimer_Register(void) {
    FUN_002b5d50();  /* Set-once guard that first runs the sibling registrars it chains to. */
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2LongTimer_metaObject,
        igLongTimer_Register,
        igLongTimer_GetPublishedMetaObject,
        thunk_igPsx2LongTimer_GetMetaObject,
        igPsx2LongTimer_className,
        0x28, /* instance size */
        igPsx2LongTimer_GetVTable,
        0,
        FUN_002cfe00,                                /* static-initializer callback item (appended on fresh configuration) */
        0                                            /* 0-terminated dependency-callback list */
    );
}
