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
extern igMetaObject *g_beNDMWLoadIntf2DegiStateCtrl_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2DegiStateCtrl_GetMetaObject(void);
extern const char beNDMWLoadIntf2DegiStateCtrl_className[];
int beNDMWLoadIntf2DegiStateCtrl_GetVTable(void);
void beNDMWLoadIntf2DegiStateCtrl_InitFields(void);
extern char g_beNDMWLoadIntf2DegiStateCtrl_callbackList[];
void *beNDMWLoadIntf2DegiStateCtrl_Register(void);
}

void *beNDMWLoadIntf2DegiStateCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2DegiStateCtrl_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2DegiStateCtrl_GetMetaObject,
        beNDMWLoadIntf2DegiStateCtrl_className,
        0x14, /* instance size */
        beNDMWLoadIntf2DegiStateCtrl_GetVTable,
        beNDMWLoadIntf2DegiStateCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DegiStateCtrl_callbackList /* callback list */
    );
}
