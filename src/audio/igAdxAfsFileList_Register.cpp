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
extern igMetaObject *g_igAdxAfsFileList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *igAdxAfsFileList_GetMetaObject(void);
extern const char igAdxAfsFileList_className[];
int igAdxAfsFileList_GetVTable(void);
extern char g_igAdxAfsFileList_callbackList[];
void *igAdxAfsFileList_Register(void);
}

void *igAdxAfsFileList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAdxAfsFileList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igAdxAfsFileList_GetMetaObject,
        igAdxAfsFileList_className,
        0x14, /* instance size */
        igAdxAfsFileList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAdxAfsFileList_callbackList /* callback list */
    );
}
