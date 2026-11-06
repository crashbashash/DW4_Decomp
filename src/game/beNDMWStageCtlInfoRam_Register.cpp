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
extern igMetaObject *g_beNDMWStageCtlInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beNDMWStageCtlInfoRam_GetMetaObject(void);
extern const char beNDMWStageCtlInfoRam_className[];
int beNDMWStageCtlInfoRam_GetVTable(void);
void *beNDMWStageCtlInfoRam_Register(void);
}

void *beNDMWStageCtlInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStageCtlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWStageCtlInfoRam_GetMetaObject,
        beNDMWStageCtlInfoRam_className,
        0x2c, /* instance size */
        beNDMWStageCtlInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
