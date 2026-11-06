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
extern igMetaObject *g_igAdxAfsFile_metaObject[];
void *igFileName_Register(void);
igMetaObject *igFileName_GetPublishedMetaObject(void);
igMetaObject *igAdxAfsFile_GetMetaObject(void);
extern const char igAdxAfsFile_className[];
int igAdxAfsFile_GetVTable(void);
void igAdxAfsFile_InitFields(void);
void *igAdxAfsFile_Register(void);
}

void *igAdxAfsFile_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAdxAfsFile_metaObject,
        igFileName_Register,
        igFileName_GetPublishedMetaObject,
        igAdxAfsFile_GetMetaObject,
        igAdxAfsFile_className,
        0x14, /* instance size */
        igAdxAfsFile_GetVTable,
        igAdxAfsFile_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
