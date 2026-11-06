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
extern igMetaObject *g_beModelCtrlWCHECK_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlWCHECK_GetMetaObject(void);
extern const char beModelCtrlWCHECK_className[];
int beModelCtrlWCHECK_GetVTable(void);
void *beModelCtrlWCHECK_Register(void);
}

void *beModelCtrlWCHECK_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlWCHECK_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlWCHECK_GetMetaObject,
        beModelCtrlWCHECK_className,
        0xc, /* instance size */
        beModelCtrlWCHECK_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
