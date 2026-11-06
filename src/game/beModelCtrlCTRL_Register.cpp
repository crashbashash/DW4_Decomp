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
extern igMetaObject *g_beModelCtrlCTRL_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlCTRL_GetMetaObject(void);
extern const char beModelCtrlCTRL_className[];
int beModelCtrlCTRL_GetVTable(void);
void *beModelCtrlCTRL_Register(void);
}

void *beModelCtrlCTRL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlCTRL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlCTRL_GetMetaObject,
        beModelCtrlCTRL_className,
        0xc, /* instance size */
        beModelCtrlCTRL_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
