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
extern igMetaObject *g_beNDMWLoadIntf2_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2_GetMetaObject(void);
extern const char beNDMWLoadIntf2_className[];
int beNDMWLoadIntf2_GetVTable(void);
void beNDMWLoadIntf2_InitFields(void);
extern char g_beNDMWLoadIntf2_callbackList[];
void *beNDMWLoadIntf2_Register(void);
}

void *beNDMWLoadIntf2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLoadIntf2_GetMetaObject,
        beNDMWLoadIntf2_className,
        0x30, /* instance size */
        beNDMWLoadIntf2_GetVTable,
        beNDMWLoadIntf2_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2_callbackList /* callback list */
    );
}
