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
extern igMetaObject *g_beCriHandle_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beCriHandle_GetMetaObject(void);
extern const char beCriHandle_className[];
int beCriHandle_GetVTable(void);
void beCriHandle_InitFields(void);
extern char g_beCriHandle_callbackList[];
void *beCriHandle_Register(void);
}

void *beCriHandle_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beCriHandle_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beCriHandle_GetMetaObject,
        beCriHandle_className,
        0x28, /* instance size */
        beCriHandle_GetVTable,
        beCriHandle_InitFields,
        0, /* extra callback item */
        g_beCriHandle_callbackList /* callback list */
    );
}
