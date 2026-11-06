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
extern igMetaObject *g_igMovieRenderer_metaObject[];
void *igRenderer_Register(void);
igMetaObject *igRenderer_GetPublishedMetaObject(void);
igMetaObject *igMovieRenderer_GetMetaObject(void);
extern const char igMovieRenderer_className[];
int igMovieRenderer_GetVTable(void);
void igMovieRenderer_InitFields(void);
extern char g_igMovieRenderer_callbackList[];
void *igMovieRenderer_Register(void);
}

void *igMovieRenderer_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieRenderer_metaObject,
        igRenderer_Register,
        igRenderer_GetPublishedMetaObject,
        igMovieRenderer_GetMetaObject,
        igMovieRenderer_className,
        0x10, /* instance size */
        igMovieRenderer_GetVTable,
        igMovieRenderer_InitFields,
        0, /* extra callback item */
        g_igMovieRenderer_callbackList /* callback list */
    );
}
