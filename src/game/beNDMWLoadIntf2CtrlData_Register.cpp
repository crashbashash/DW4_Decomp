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
extern igMetaObject *g_beNDMWLoadIntf2CtrlData_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2CtrlData_GetMetaObject(void);
extern const char beNDMWLoadIntf2CtrlData_className[];
int beNDMWLoadIntf2CtrlData_GetVTable(void);
void beNDMWLoadIntf2CtrlData_InitFields(void);
void *beNDMWLoadIntf2CtrlData_Register(void);
}

void *beNDMWLoadIntf2CtrlData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2CtrlData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2CtrlData_GetMetaObject,
        beNDMWLoadIntf2CtrlData_className,
        0x34, /* instance size */
        beNDMWLoadIntf2CtrlData_GetVTable,
        beNDMWLoadIntf2CtrlData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
