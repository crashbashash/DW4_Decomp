struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_libNdmwRuntimePlugin_metaObject[];
void *igInsightPlugin_Register(void);
igMetaObject *igInsightPlugin_GetPublishedMetaObject(void);
igMetaObject *libNdmwRuntimePlugin_GetMetaObject(void);
extern const char libNdmwRuntimePlugin_className[];
int libNdmwRuntimePlugin_GetVTable(void);
void libNdmwRuntimePlugin_InitFields(void);
extern char g_libNdmwRuntimePlugin_callbackList[];
void *libNdmwRuntimePlugin_Register(void);
}

void *libNdmwRuntimePlugin_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_libNdmwRuntimePlugin_metaObject,
        igInsightPlugin_Register,
        igInsightPlugin_GetPublishedMetaObject,
        libNdmwRuntimePlugin_GetMetaObject,
        libNdmwRuntimePlugin_className,
        0x5c, /* instance size */
        libNdmwRuntimePlugin_GetVTable,
        libNdmwRuntimePlugin_InitFields,
        0, /* extra callback item */
        g_libNdmwRuntimePlugin_callbackList /* callback list */
    );
}
