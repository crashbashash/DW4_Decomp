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
extern igMetaObject *g_beModelCtrlSCEffect_metaObject[];
void *beModelCtrlSubComBase_Register(void);
igMetaObject *beModelCtrlSubComBase_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlSCEffect_GetMetaObject(void);
extern const char beModelCtrlSCEffect_className[];
int beModelCtrlSCEffect_GetVTable(void);
void beModelCtrlSCEffect_InitFields(void);
void *beModelCtrlSCEffect_Register(void);
}

void *beModelCtrlSCEffect_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlSCEffect_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCEffect_GetMetaObject,
        beModelCtrlSCEffect_className,
        0x3c, /* instance size */
        beModelCtrlSCEffect_GetVTable,
        beModelCtrlSCEffect_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
