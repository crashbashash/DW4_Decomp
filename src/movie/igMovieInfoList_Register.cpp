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
extern igMetaObject *g_igMovieInfoList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *igMovieInfoList_GetMetaObject(void);
extern const char igMovieInfoList_className[];
int igMovieInfoList_GetVTable(void);
extern char g_igMovieInfoList_callbackList[];
void *igMovieInfoList_Register(void);
}

void *igMovieInfoList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieInfoList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMovieInfoList_GetMetaObject,
        igMovieInfoList_className,
        0x14, /* instance size */
        igMovieInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMovieInfoList_callbackList /* callback list */
    );
}
