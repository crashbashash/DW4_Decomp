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
extern igMetaObject *g_beModelCtrlLABELCTRL_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlLABELCTRL_GetMetaObject(void);
extern const char beModelCtrlLABELCTRL_className[];
int beModelCtrlLABELCTRL_GetVTable(void);
void beModelCtrlLABELCTRL_InitFields(void);
void *beModelCtrlLABELCTRL_Register(void);
}

void *beModelCtrlLABELCTRL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlLABELCTRL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLABELCTRL_GetMetaObject,
        beModelCtrlLABELCTRL_className,
        0x10, /* instance size */
        beModelCtrlLABELCTRL_GetVTable,
        beModelCtrlLABELCTRL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
