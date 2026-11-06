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
extern igMetaObject *g_igCriMovieCodec_metaObject[];
void *igMovieCodec_Register(void);
igMetaObject *igMovieCodec_GetPublishedMetaObject(void);
igMetaObject *igCriMovieCodec_GetMetaObject(void);
extern const char igCriMovieCodec_className[];
int igCriMovieCodec_GetVTable(void);
void igCriMovieCodec_InitFields(void);
extern char g_igCriMovieCodec_callbackList[];
void *igCriMovieCodec_Register(void);
}

void *igCriMovieCodec_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCriMovieCodec_metaObject,
        igMovieCodec_Register,
        igMovieCodec_GetPublishedMetaObject,
        igCriMovieCodec_GetMetaObject,
        igCriMovieCodec_className,
        0x18, /* instance size */
        igCriMovieCodec_GetVTable,
        igCriMovieCodec_InitFields,
        0, /* extra callback item */
        g_igCriMovieCodec_callbackList /* callback list */
    );
}
