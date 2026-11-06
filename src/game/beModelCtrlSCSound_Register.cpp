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
extern igMetaObject *g_beModelCtrlSCSound_metaObject[];
void *beModelCtrlSubComBase_Register(void);
igMetaObject *beModelCtrlSubComBase_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlSCSound_GetMetaObject(void);
extern const char beModelCtrlSCSound_className[];
int beModelCtrlSCSound_GetVTable(void);
void beModelCtrlSCSound_InitFields(void);
void *beModelCtrlSCSound_Register(void);
}

void *beModelCtrlSCSound_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlSCSound_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCSound_GetMetaObject,
        beModelCtrlSCSound_className,
        0x20, /* instance size */
        beModelCtrlSCSound_GetVTable,
        beModelCtrlSCSound_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
