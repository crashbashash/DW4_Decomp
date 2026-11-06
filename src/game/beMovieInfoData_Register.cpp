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
extern igMetaObject *g_beMovieInfoData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beMovieInfoData_GetMetaObject(void);
extern const char beMovieInfoData_className[];
int beMovieInfoData_GetVTable(void);
void beMovieInfoData_InitFields(void);
extern char g_beMovieInfoData_callbackList[];
void *beMovieInfoData_Register(void);
}

void *beMovieInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMovieInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beMovieInfoData_GetMetaObject,
        beMovieInfoData_className,
        0x1c, /* instance size */
        beMovieInfoData_GetVTable,
        beMovieInfoData_InitFields,
        0, /* extra callback item */
        g_beMovieInfoData_callbackList /* callback list */
    );
}
