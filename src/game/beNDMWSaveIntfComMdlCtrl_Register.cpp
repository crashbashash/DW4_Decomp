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
extern igMetaObject *g_beNDMWSaveIntfComMdlCtrl_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWSaveIntfComMdlCtrl_GetMetaObject(void);
extern const char beNDMWSaveIntfComMdlCtrl_className[];
int beNDMWSaveIntfComMdlCtrl_GetVTable(void);
void beNDMWSaveIntfComMdlCtrl_InitFields(void);
extern char g_beNDMWSaveIntfComMdlCtrl_callbackList[];
void *beNDMWSaveIntfComMdlCtrl_Register(void);
}

void *beNDMWSaveIntfComMdlCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWSaveIntfComMdlCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWSaveIntfComMdlCtrl_GetMetaObject,
        beNDMWSaveIntfComMdlCtrl_className,
        0x28, /* instance size */
        beNDMWSaveIntfComMdlCtrl_GetVTable,
        beNDMWSaveIntfComMdlCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveIntfComMdlCtrl_callbackList /* callback list */
    );
}
