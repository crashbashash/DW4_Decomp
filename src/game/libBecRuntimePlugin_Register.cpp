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
extern igMetaObject *g_libBecRuntimePlugin_metaObject[];
void *igInsightPlugin_Register(void);
igMetaObject *igInsightPlugin_GetPublishedMetaObject(void);
igMetaObject *libBecRuntimePlugin_GetMetaObject(void);
extern const char libBecRuntimePlugin_className[];
int libBecRuntimePlugin_GetVTable(void);
void libBecRuntimePlugin_InitFields(void);
extern char g_libBecRuntimePlugin_callbackList[];
void *libBecRuntimePlugin_Register(void);
}

void *libBecRuntimePlugin_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_libBecRuntimePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        libBecRuntimePlugin_GetMetaObject,
        libBecRuntimePlugin_className,
        0xa4, /* instance size */
        libBecRuntimePlugin_GetVTable,
        libBecRuntimePlugin_InitFields,
        0, /* extra callback item */
        g_libBecRuntimePlugin_callbackList /* callback list */
    );
}
