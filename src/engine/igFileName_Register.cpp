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
extern igMetaObject *g_igFileName_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *igFileName_GetMetaObject(void);
extern const char igFileName_className[];
int igFileName_GetVTable(void);
void igFileName_InitFields(void);
extern char g_igFileName_callbackList[];
void *igFileName_Register(void);
}

void *igFileName_Register(void) {
    AdxMovieLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_igFileName_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        igFileName_GetMetaObject,
        igFileName_className,
        0x10, /* instance size */
        igFileName_GetVTable,
        igFileName_InitFields,
        0, /* extra callback item */
        g_igFileName_callbackList /* callback list */
    );
}
