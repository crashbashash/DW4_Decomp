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
extern igMetaObject *g_beNDMWLoadIntf2Diffselect_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2Diffselect_GetMetaObject(void);
extern const char beNDMWLoadIntf2Diffselect_className[];
int beNDMWLoadIntf2Diffselect_GetVTable(void);
void beNDMWLoadIntf2Diffselect_InitFields(void);
extern char g_beNDMWLoadIntf2Diffselect_callbackList[];
void *beNDMWLoadIntf2Diffselect_Register(void);
}

void *beNDMWLoadIntf2Diffselect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2Diffselect_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2Diffselect_GetMetaObject,
        beNDMWLoadIntf2Diffselect_className,
        0x4c, /* instance size */
        beNDMWLoadIntf2Diffselect_GetVTable,
        beNDMWLoadIntf2Diffselect_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2Diffselect_callbackList /* callback list */
    );
}
