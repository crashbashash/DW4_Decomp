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
extern igMetaObject *g_beModelCtrlMOVE_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlMOVE_GetMetaObject(void);
extern const char beModelCtrlMOVE_className[];
int beModelCtrlMOVE_GetVTable(void);
void beModelCtrlMOVE_InitFields(void);
void *beModelCtrlMOVE_Register(void);
}

void *beModelCtrlMOVE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMOVE_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVE_GetMetaObject,
        beModelCtrlMOVE_className,
        0x14, /* instance size */
        beModelCtrlMOVE_GetVTable,
        beModelCtrlMOVE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
