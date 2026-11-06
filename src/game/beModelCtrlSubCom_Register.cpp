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
extern igMetaObject *g_beModelCtrlSubCom_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beModelCtrlSubCom_GetMetaObject(void);
extern const char beModelCtrlSubCom_className[];
int beModelCtrlSubCom_GetVTable(void);
void beModelCtrlSubCom_InitFields(void);
extern char g_beModelCtrlSubCom_callbackList[];
void *beModelCtrlSubCom_Register(void);
}

void *beModelCtrlSubCom_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlSubCom_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlSubCom_GetMetaObject,
        beModelCtrlSubCom_className,
        0xc, /* instance size */
        beModelCtrlSubCom_GetVTable,
        beModelCtrlSubCom_InitFields,
        0, /* extra callback item */
        g_beModelCtrlSubCom_callbackList /* callback list */
    );
}
