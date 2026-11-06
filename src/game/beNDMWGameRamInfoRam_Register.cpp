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
extern igMetaObject *g_beNDMWGameRamInfoRam_metaObject[];
void *beBaseInfoRam_Register(void);
igMetaObject *beBaseInfoRam_GetPublishedMetaObject(void);
igMetaObject *beNDMWGameRamInfoRam_GetMetaObject(void);
extern const char beNDMWGameRamInfoRam_className[];
int beNDMWGameRamInfoRam_GetVTable(void);
void *beNDMWGameRamInfoRam_Register(void);
}

void *beNDMWGameRamInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWGameRamInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWGameRamInfoRam_GetMetaObject,
        beNDMWGameRamInfoRam_className,
        0x2c, /* instance size */
        beNDMWGameRamInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
