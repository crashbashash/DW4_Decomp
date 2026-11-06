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
extern igMetaObject *g_beModelCtrlJUMP_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlJUMP_GetMetaObject(void);
extern const char beModelCtrlJUMP_className[];
int beModelCtrlJUMP_GetVTable(void);
void *beModelCtrlJUMP_Register(void);
}

void *beModelCtrlJUMP_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlJUMP_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlJUMP_GetMetaObject,
        beModelCtrlJUMP_className,
        0xc, /* instance size */
        beModelCtrlJUMP_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
