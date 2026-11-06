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
extern igMetaObject *g_beNDMWLoadIntf2ComMdlCtrl_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2ComMdlCtrl_GetMetaObject(void);
extern const char beNDMWLoadIntf2ComMdlCtrl_className[];
int beNDMWLoadIntf2ComMdlCtrl_GetVTable(void);
void beNDMWLoadIntf2ComMdlCtrl_InitFields(void);
extern char g_beNDMWLoadIntf2ComMdlCtrl_callbackList[];
void *beNDMWLoadIntf2ComMdlCtrl_Register(void);
}

void *beNDMWLoadIntf2ComMdlCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2ComMdlCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2ComMdlCtrl_GetMetaObject,
        beNDMWLoadIntf2ComMdlCtrl_className,
        0x28, /* instance size */
        beNDMWLoadIntf2ComMdlCtrl_GetVTable,
        beNDMWLoadIntf2ComMdlCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2ComMdlCtrl_callbackList /* callback list */
    );
}
