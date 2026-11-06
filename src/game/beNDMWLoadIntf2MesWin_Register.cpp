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
extern igMetaObject *g_beNDMWLoadIntf2MesWin_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2MesWin_GetMetaObject(void);
extern const char beNDMWLoadIntf2MesWin_className[];
int beNDMWLoadIntf2MesWin_GetVTable(void);
void beNDMWLoadIntf2MesWin_InitFields(void);
extern char g_beNDMWLoadIntf2MesWin_callbackList[];
void *beNDMWLoadIntf2MesWin_Register(void);
}

void *beNDMWLoadIntf2MesWin_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2MesWin_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2MesWin_GetMetaObject,
        beNDMWLoadIntf2MesWin_className,
        0x40, /* instance size */
        beNDMWLoadIntf2MesWin_GetVTable,
        beNDMWLoadIntf2MesWin_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2MesWin_callbackList /* callback list */
    );
}
