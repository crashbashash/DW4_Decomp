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
extern igMetaObject *g_beSelectCtrlInfoWork_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beSelectCtrlInfoWork_GetMetaObject(void);
extern const char beSelectCtrlInfoWork_className[];
int beSelectCtrlInfoWork_GetVTable(void);
void beSelectCtrlInfoWork_InitFields(void);
extern char g_beSelectCtrlInfoWork_callbackList[];
void *beSelectCtrlInfoWork_Register(void);
}

void *beSelectCtrlInfoWork_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beSelectCtrlInfoWork_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beSelectCtrlInfoWork_GetMetaObject,
        beSelectCtrlInfoWork_className,
        0x24, /* instance size */
        beSelectCtrlInfoWork_GetVTable,
        beSelectCtrlInfoWork_InitFields,
        0, /* extra callback item */
        g_beSelectCtrlInfoWork_callbackList /* callback list */
    );
}
