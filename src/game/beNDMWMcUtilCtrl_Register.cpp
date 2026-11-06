struct igMetaObject;
extern "C" {
void NdmwLibrary_MarkRegistered(void);
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
extern igMetaObject *g_beNDMWMcUtilCtrl_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWMcUtilCtrl_GetMetaObject(void);
extern const char beNDMWMcUtilCtrl_className[];
int beNDMWMcUtilCtrl_GetVTable(void);
void beNDMWMcUtilCtrl_InitFields(void);
extern char g_beNDMWMcUtilCtrl_callbackList[];
void *beNDMWMcUtilCtrl_Register(void);
}

void *beNDMWMcUtilCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMcUtilCtrl_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWMcUtilCtrl_GetMetaObject,
        beNDMWMcUtilCtrl_className,
        0x40, /* instance size */
        beNDMWMcUtilCtrl_GetVTable,
        beNDMWMcUtilCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWMcUtilCtrl_callbackList /* callback list */
    );
}
