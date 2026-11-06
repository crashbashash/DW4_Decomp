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
extern igMetaObject *g_beNDMWLoadIntf2TextOrder_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2TextOrder_GetMetaObject(void);
extern const char beNDMWLoadIntf2TextOrder_className[];
int beNDMWLoadIntf2TextOrder_GetVTable(void);
void beNDMWLoadIntf2TextOrder_InitFields(void);
extern char g_beNDMWLoadIntf2TextOrder_callbackList[];
void *beNDMWLoadIntf2TextOrder_Register(void);
}

void *beNDMWLoadIntf2TextOrder_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2TextOrder_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2TextOrder_GetMetaObject,
        beNDMWLoadIntf2TextOrder_className,
        0x18, /* instance size */
        beNDMWLoadIntf2TextOrder_GetVTable,
        beNDMWLoadIntf2TextOrder_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2TextOrder_callbackList /* callback list */
    );
}
