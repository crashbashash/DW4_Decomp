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
extern igMetaObject *g_igMovieCodec_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *igMovieCodec_GetMetaObject(void);
extern const char igMovieCodec_className[];
int igMovieCodec_GetVTable(void);
void *igMovieCodec_Register(void);
}

void *igMovieCodec_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieCodec_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igMovieCodec_GetMetaObject,
        igMovieCodec_className,
        0xc, /* instance size */
        igMovieCodec_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
