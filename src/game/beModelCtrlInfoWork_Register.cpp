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
extern igMetaObject *g_beModelCtrlInfoWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beModelCtrlInfoWork_GetMetaObject(void);
extern const char beModelCtrlInfoWork_className[];
int beModelCtrlInfoWork_GetVTable(void);
void beModelCtrlInfoWork_InitFields(void);
extern char g_beModelCtrlInfoWork_callbackList[];
void *beModelCtrlInfoWork_Register(void);
}

void *beModelCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beModelCtrlInfoWork_GetMetaObject,
        beModelCtrlInfoWork_className,
        0xec, /* instance size */
        beModelCtrlInfoWork_GetVTable,
        beModelCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beModelCtrlInfoWork_callbackList /* callback list */
    );
}
