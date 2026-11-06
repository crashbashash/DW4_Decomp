extern char igUnsignedIntListNoClean_Register[];
extern char igCallStackTracer_GetVTable[];
extern char thunk_igCallStackTracer_GetMetaObject[];
extern char igUnsignedIntListNoClean_GetPublishedMetaObject[];
extern char igCallStackTracer_className[];
extern char g_igCallStackTracer_metaObject[];
int FUN_002b5d50();
int igMetaObject_RegisterClass();
void FUN_002cc7b0(void);
void igCallStackTracer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCallStackTracer_metaObject,
        igUnsignedIntListNoClean_Register,
        igUnsignedIntListNoClean_GetPublishedMetaObject,
        thunk_igCallStackTracer_GetMetaObject,
        igCallStackTracer_className,
        0x14, /* instance size */
        igCallStackTracer_GetVTable,
        FUN_002cc7b0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
