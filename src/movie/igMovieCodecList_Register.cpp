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
extern igMetaObject *g_igMovieCodecList_metaObject[];
void *igObjectList_Register(void);
igMetaObject *igObjectList_GetPublishedMetaObject(void);
igMetaObject *igMovieCodecList_GetMetaObject(void);
extern const char igMovieCodecList_className[];
int igMovieCodecList_GetVTable(void);
extern char g_igMovieCodecList_callbackList[];
void *igMovieCodecList_Register(void);
}

void *igMovieCodecList_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieCodecList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igMovieCodecList_GetMetaObject,
        igMovieCodecList_className,
        0x14, /* instance size */
        igMovieCodecList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMovieCodecList_callbackList /* callback list */
    );
}
