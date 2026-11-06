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
extern igMetaObject *g_beModelCtrlMOVERL_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlMOVERL_GetMetaObject(void);
extern const char beModelCtrlMOVERL_className[];
int beModelCtrlMOVERL_GetVTable(void);
void beModelCtrlMOVERL_InitFields(void);
void *beModelCtrlMOVERL_Register(void);
}

void *beModelCtrlMOVERL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMOVERL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVERL_GetMetaObject,
        beModelCtrlMOVERL_className,
        0x14, /* instance size */
        beModelCtrlMOVERL_GetVTable,
        beModelCtrlMOVERL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
