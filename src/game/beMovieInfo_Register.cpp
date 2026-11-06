struct igMetaObject;
extern "C" {
void BecLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beMovieInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beMovieInfo_GetMetaObject(void);
extern const char beMovieInfo_className[];
int beMovieInfo_GetVTable(void);
void *beMovieInfo_Register(void);
}

void *beMovieInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMovieInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beMovieInfo_GetMetaObject,
        beMovieInfo_className,
        0x1c, /* instance size */
        beMovieInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
