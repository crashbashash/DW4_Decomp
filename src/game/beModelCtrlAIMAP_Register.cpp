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
extern igMetaObject *g_beModelCtrlAIMAP_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlAIMAP_GetMetaObject(void);
extern const char beModelCtrlAIMAP_className[];
int beModelCtrlAIMAP_GetVTable(void);
void *beModelCtrlAIMAP_Register(void);
}

void *beModelCtrlAIMAP_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIMAP_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlAIMAP_GetMetaObject,
        beModelCtrlAIMAP_className,
        0xc, /* instance size */
        beModelCtrlAIMAP_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
