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
extern igMetaObject *g_beNDMWLoadIntf2DataSelIntf_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2DataSelIntf_GetMetaObject(void);
extern const char beNDMWLoadIntf2DataSelIntf_className[];
int beNDMWLoadIntf2DataSelIntf_GetVTable(void);
void beNDMWLoadIntf2DataSelIntf_InitFields(void);
extern char g_beNDMWLoadIntf2DataSelIntf_callbackList[];
void *beNDMWLoadIntf2DataSelIntf_Register(void);
}

void *beNDMWLoadIntf2DataSelIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2DataSelIntf_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2DataSelIntf_GetMetaObject,
        beNDMWLoadIntf2DataSelIntf_className,
        0x5c, /* instance size */
        beNDMWLoadIntf2DataSelIntf_GetVTable,
        beNDMWLoadIntf2DataSelIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2DataSelIntf_callbackList /* callback list */
    );
}
