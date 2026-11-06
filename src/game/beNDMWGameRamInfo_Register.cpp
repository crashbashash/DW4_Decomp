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
extern igMetaObject *g_beNDMWGameRamInfo_metaObject[];
void *beBaseInfo_Register(void);
igMetaObject *beBaseInfo_GetPublishedMetaObject(void);
igMetaObject *beNDMWGameRamInfo_GetMetaObject(void);
extern const char beNDMWGameRamInfo_className[];
int beNDMWGameRamInfo_GetVTable(void);
void *beNDMWGameRamInfo_Register(void);
}

void *beNDMWGameRamInfo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWGameRamInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beNDMWGameRamInfo_GetMetaObject,
        beNDMWGameRamInfo_className,
        0x1c, /* instance size */
        beNDMWGameRamInfo_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}
