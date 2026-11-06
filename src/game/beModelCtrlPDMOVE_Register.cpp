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
extern igMetaObject *g_beModelCtrlPDMOVE_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlPDMOVE_GetMetaObject(void);
extern const char beModelCtrlPDMOVE_className[];
int beModelCtrlPDMOVE_GetVTable(void);
void beModelCtrlPDMOVE_InitFields(void);
void *beModelCtrlPDMOVE_Register(void);
}

void *beModelCtrlPDMOVE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlPDMOVE_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlPDMOVE_GetMetaObject,
        beModelCtrlPDMOVE_className,
        0x14, /* instance size */
        beModelCtrlPDMOVE_GetVTable,
        beModelCtrlPDMOVE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
