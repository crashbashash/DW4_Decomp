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
extern igMetaObject *g_beNDMWLoadCtrl2CommonIntf_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadCtrl2CommonIntf_GetMetaObject(void);
extern const char beNDMWLoadCtrl2CommonIntf_className[];
int beNDMWLoadCtrl2CommonIntf_GetVTable(void);
void beNDMWLoadCtrl2CommonIntf_InitFields(void);
extern char g_beNDMWLoadCtrl2CommonIntf_callbackList[];
void *beNDMWLoadCtrl2CommonIntf_Register(void);
}

void *beNDMWLoadCtrl2CommonIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadCtrl2CommonIntf_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadCtrl2CommonIntf_GetMetaObject,
        beNDMWLoadCtrl2CommonIntf_className,
        0x48, /* instance size */
        beNDMWLoadCtrl2CommonIntf_GetVTable,
        beNDMWLoadCtrl2CommonIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2CommonIntf_callbackList /* callback list */
    );
}
