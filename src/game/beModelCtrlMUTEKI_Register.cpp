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
extern igMetaObject *g_beModelCtrlMUTEKI_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlMUTEKI_GetMetaObject(void);
extern const char beModelCtrlMUTEKI_className[];
int beModelCtrlMUTEKI_GetVTable(void);
void beModelCtrlMUTEKI_InitFields(void);
void *beModelCtrlMUTEKI_Register(void);
}

void *beModelCtrlMUTEKI_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMUTEKI_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMUTEKI_GetMetaObject,
        beModelCtrlMUTEKI_className,
        0x10, /* instance size */
        beModelCtrlMUTEKI_GetVTable,
        beModelCtrlMUTEKI_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
