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
extern igMetaObject *g_beModelCtrlAIData_metaObject[];
void *igNamedObject_Register(void);
igMetaObject *igNamedObject_GetPublishedMetaObject(void);
igMetaObject *beModelCtrlAIData_GetMetaObject(void);
extern const char beModelCtrlAIData_className[];
int beModelCtrlAIData_GetVTable(void);
void beModelCtrlAIData_InitFields(void);
void *beModelCtrlAIData_Register(void);
}

void *beModelCtrlAIData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlAIData_GetMetaObject,
        beModelCtrlAIData_className,
        0x18, /* instance size */
        beModelCtrlAIData_GetVTable,
        beModelCtrlAIData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
