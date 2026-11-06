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
extern igMetaObject *g_igMoviePlugin_metaObject[];
void *igInsightPlugin_Register(void);
igMetaObject *igInsightPlugin_GetPublishedMetaObject(void);
igMetaObject *igMoviePlugin_GetMetaObject(void);
extern const char igMoviePlugin_className[];
int igMoviePlugin_GetVTable(void);
void igMoviePlugin_InitFields(void);
extern char g_igMoviePlugin_callbackList[];
void *igMoviePlugin_Register(void);
}

void *igMoviePlugin_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMoviePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        igMoviePlugin_GetMetaObject,
        igMoviePlugin_className,
        0xc, /* instance size */
        igMoviePlugin_GetVTable,
        igMoviePlugin_InitFields,
        0, /* extra callback item */
        g_igMoviePlugin_callbackList /* callback list */
    );
}
