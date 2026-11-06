extern char igCallStackTracer_Register[];
extern char thunk_igPsx2CallStackTracer_GetMetaObject[];
extern char igPsx2CallStackTracer_GetVTable[];
extern char igCallStackTracer_GetPublishedMetaObject[];
extern char igPsx2CallStackTracer_className[];
extern char g_igPsx2CallStackTracer_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
extern int igPsx2CallStackTracer_InitFields_002d0530[4];
void igPsx2CallStackTracer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2CallStackTracer_metaObject,
        igCallStackTracer_Register,
        igCallStackTracer_GetPublishedMetaObject,
        thunk_igPsx2CallStackTracer_GetMetaObject,
        igPsx2CallStackTracer_className,
        0x14, /* instance size */
        igPsx2CallStackTracer_GetVTable,
        &igPsx2CallStackTracer_InitFields_002d0530[0],     /* Field adder. */
        0,                                                 /* extra callback-vector item (none) */
        0                                                  /* zero-terminated callback-vector item list (none) */
    );
}
