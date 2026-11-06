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
extern igMetaObject *g_beNDMWLoadIntf2SelSlot_metaObject[];
void *beBaseInfoData_Register(void);
igMetaObject *beBaseInfoData_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2SelSlot_GetMetaObject(void);
extern const char beNDMWLoadIntf2SelSlot_className[];
int beNDMWLoadIntf2SelSlot_GetVTable(void);
void beNDMWLoadIntf2SelSlot_InitFields(void);
extern char g_beNDMWLoadIntf2SelSlot_callbackList[];
void *beNDMWLoadIntf2SelSlot_Register(void);
}

void *beNDMWLoadIntf2SelSlot_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2SelSlot_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beNDMWLoadIntf2SelSlot_GetMetaObject,
        beNDMWLoadIntf2SelSlot_className,
        0x5c, /* instance size */
        beNDMWLoadIntf2SelSlot_GetVTable,
        beNDMWLoadIntf2SelSlot_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2SelSlot_callbackList /* callback list */
    );
}
