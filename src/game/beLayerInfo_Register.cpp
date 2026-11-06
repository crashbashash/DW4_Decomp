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
extern igMetaObject *g_beLayerInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beLayerInfo_GetMetaObject(void);
extern const char beLayerInfo_className[];
int beLayerInfo_GetVTable(void);
void beLayerInfo_InitFields(void);
extern char g_beLayerInfo_callbackList[];
void *beLayerInfo_Register(void);
}

void *beLayerInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beLayerInfo_GetMetaObject,
        beLayerInfo_className,
        0x20, /* instance size */
        beLayerInfo_GetVTable,
        beLayerInfo_InitFields,
        0, /* extra callback item */
        g_beLayerInfo_callbackList /* callback list */
    );
}
