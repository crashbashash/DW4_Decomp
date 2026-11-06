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
extern igMetaObject *g_beNDMWLoadIntf2ChrDataSel_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2ChrDataSel_GetMetaObject(void);
extern const char beNDMWLoadIntf2ChrDataSel_className[];
int beNDMWLoadIntf2ChrDataSel_GetVTable(void);
void beNDMWLoadIntf2ChrDataSel_InitFields(void);
extern char g_beNDMWLoadIntf2ChrDataSel_callbackList[];
void *beNDMWLoadIntf2ChrDataSel_Register(void);
}

void *beNDMWLoadIntf2ChrDataSel_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2ChrDataSel_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2ChrDataSel_GetMetaObject,
        beNDMWLoadIntf2ChrDataSel_className,
        0x4c, /* instance size */
        beNDMWLoadIntf2ChrDataSel_GetVTable,
        beNDMWLoadIntf2ChrDataSel_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2ChrDataSel_callbackList /* callback list */
    );
}
