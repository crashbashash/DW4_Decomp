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
extern igMetaObject *g_beNDMWShinkaCtrl_metaObject[];
void *igObject_Register(void);
igMetaObject *igObject_GetMetaObject_ParentAccessor(void);
igMetaObject *beNDMWShinkaCtrl_GetMetaObject(void);
extern const char beNDMWShinkaCtrl_className[];
int beNDMWShinkaCtrl_GetVTable(void);
void beNDMWShinkaCtrl_InitFields(void);
extern char g_beNDMWShinkaCtrl_callbackList[];
void *beNDMWShinkaCtrl_Register(void);
}

void *beNDMWShinkaCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShinkaCtrl_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        beNDMWShinkaCtrl_GetMetaObject,
        beNDMWShinkaCtrl_className,
        0x20, /* instance size */
        beNDMWShinkaCtrl_GetVTable,
        beNDMWShinkaCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWShinkaCtrl_callbackList /* callback list */
    );
}
