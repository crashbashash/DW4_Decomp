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
extern igMetaObject *g_beNDMWStageCtl_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWStageCtl_GetMetaObject(void);
extern const char beNDMWStageCtl_className[];
int beNDMWStageCtl_GetVTable(void);
void beNDMWStageCtl_InitFields(void);
void *beNDMWStageCtl_Register(void);
}

void *beNDMWStageCtl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStageCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWStageCtl_GetMetaObject,
        beNDMWStageCtl_className,
        0x28, /* instance size */
        beNDMWStageCtl_GetVTable,
        beNDMWStageCtl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}
