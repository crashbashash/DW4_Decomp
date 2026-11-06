struct igMetaObject;
extern "C" {
void AdxMovieLibrary_MarkRegistered(void);
void *igMetaObject_RegisterClass(
        int abstractState,
        igMetaObject **slot,
        void *(*baseRegister)(void),
        igMetaObject *(*baseMetaObject)(void),
        igMetaObject *(*getMetaObject)(void),
        const char *className,
        int instanceSize,
        int (*getVTable)(void),
        void (*initFields)(void),
        void (*callbackItem)(void),
        void *callbackList);
extern igMetaObject *g_igAdxFile_metaObject[];
void *igFile_Register(void);
igMetaObject *igFile_GetPublishedMetaObject(void);
igMetaObject *igAdxFile_GetMetaObject(void);
extern const char igAdxFile_className[];
int igAdxFile_GetVTable(void);
void igAdxFile_InitFields(void);
void FUN_003350b0(void);
void *igAdxFile_Register(void);
}

void *igAdxFile_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAdxFile_metaObject,
        igFile_Register,
        igFile_GetPublishedMetaObject,
        igAdxFile_GetMetaObject,
        igAdxFile_className,
        0x68, /* instance size */
        igAdxFile_GetVTable,
        igAdxFile_InitFields,
        FUN_003350b0, /* extra callback item */
        0 /* callback list */
    );
}
