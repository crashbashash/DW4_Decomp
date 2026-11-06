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
extern igMetaObject *g_igMovieManager_metaObject[];
void *igInfoManager_Register(void);
igMetaObject *igInfoManager_GetPublishedMetaObject(void);
igMetaObject *igMovieManager_GetMetaObject(void);
extern const char igMovieManager_className[];
int igMovieManager_GetVTable(void);
void igMovieManager_InitFields(void);
extern char g_igMovieManager_callbackList[];
void *igMovieManager_Register(void);
}

void *igMovieManager_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMovieManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        igMovieManager_GetMetaObject,
        igMovieManager_className,
        0x28, /* instance size */
        igMovieManager_GetVTable,
        igMovieManager_InitFields,
        0, /* extra callback item */
        g_igMovieManager_callbackList /* callback list */
    );
}
