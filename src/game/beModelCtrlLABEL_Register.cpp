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
extern igMetaObject *g_beModelCtrlLABEL_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlLABEL_GetMetaObject(void);
extern const char beModelCtrlLABEL_className[];
int beModelCtrlLABEL_GetVTable(void);
void *beModelCtrlLABEL_Register(void);
}

void *beModelCtrlLABEL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlLABEL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLABEL_GetMetaObject,
        beModelCtrlLABEL_className,
        0xc, /* instance size */
        beModelCtrlLABEL_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
