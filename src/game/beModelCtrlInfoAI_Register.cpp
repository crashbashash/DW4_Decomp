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
extern igMetaObject *g_beModelCtrlInfoAI_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beModelCtrlInfoAI_GetMetaObject(void);
extern const char beModelCtrlInfoAI_className[];
int beModelCtrlInfoAI_GetVTable(void);
void beModelCtrlInfoAI_InitFields(void);
void *beModelCtrlInfoAI_Register(void);
}

void *beModelCtrlInfoAI_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoAI_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoAI_GetMetaObject,
        beModelCtrlInfoAI_className,
        0x24, /* instance size */
        beModelCtrlInfoAI_GetVTable,
        beModelCtrlInfoAI_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
