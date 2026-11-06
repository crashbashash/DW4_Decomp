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
extern igMetaObject *g_beNDMWLoadIntf2NameSel_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2NameSel_GetMetaObject(void);
extern const char beNDMWLoadIntf2NameSel_className[];
int beNDMWLoadIntf2NameSel_GetVTable(void);
void beNDMWLoadIntf2NameSel_InitFields(void);
extern char g_beNDMWLoadIntf2NameSel_callbackList[];
void *beNDMWLoadIntf2NameSel_Register(void);
}

void *beNDMWLoadIntf2NameSel_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2NameSel_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2NameSel_GetMetaObject,
        beNDMWLoadIntf2NameSel_className,
        0x120, /* instance size */
        beNDMWLoadIntf2NameSel_GetVTable,
        beNDMWLoadIntf2NameSel_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2NameSel_callbackList /* callback list */
    );
}
