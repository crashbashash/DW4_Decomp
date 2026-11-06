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
extern igMetaObject *g_igMovieInfo_metaObject[];
void *igInfo_Register(void);
igMetaObject *igInfo_GetPublishedMetaObject(void);
igMetaObject *igMovieInfo_GetMetaObject(void);
extern const char igMovieInfo_className[];
int igMovieInfo_GetVTable(void);
void igMovieInfo_InitFields(void);
extern char g_igMovieInfo_callbackList[];
void *igMovieInfo_Register(void);
}

void *igMovieInfo_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        igMovieInfo_GetMetaObject,
        igMovieInfo_className,
        0x68, /* instance size */
        igMovieInfo_GetVTable,
        igMovieInfo_InitFields,
        0, /* extra callback item */
        g_igMovieInfo_callbackList /* callback list */
    );
}
