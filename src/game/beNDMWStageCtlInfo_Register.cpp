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
extern igMetaObject *g_beNDMWStageCtlInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWStageCtlInfo_GetMetaObject(void);
extern const char beNDMWStageCtlInfo_className[];
int beNDMWStageCtlInfo_GetVTable(void);
void *beNDMWStageCtlInfo_Register(void);
}

void *beNDMWStageCtlInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStageCtlInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWStageCtlInfo_GetMetaObject,
        beNDMWStageCtlInfo_className,
        0x1c, /* instance size */
        beNDMWStageCtlInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
