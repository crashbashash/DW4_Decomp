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
extern igMetaObject *g_beNDMWLoadIntf2Info_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWLoadIntf2Info_GetMetaObject(void);
extern const char beNDMWLoadIntf2Info_className[];
int beNDMWLoadIntf2Info_GetVTable(void);
void *beNDMWLoadIntf2Info_Register(void);
}

void *beNDMWLoadIntf2Info_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWLoadIntf2Info_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWLoadIntf2Info_GetMetaObject,
        beNDMWLoadIntf2Info_className,
        0x1c, /* instance size */
        beNDMWLoadIntf2Info_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
