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
extern igMetaObject *g_beNDMWGameRam_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWGameRam_GetMetaObject(void);
extern const char beNDMWGameRam_className[];
int beNDMWGameRam_GetVTable(void);
void beNDMWGameRam_InitFields(void);
extern char g_beNDMWGameRam_callbackList[];
void *beNDMWGameRam_Register(void);
}

void *beNDMWGameRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWGameRam_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWGameRam_GetMetaObject,
        beNDMWGameRam_className,
        0x4c, /* instance size */
        beNDMWGameRam_GetVTable,
        beNDMWGameRam_InitFields,
        0, /* extra callback item */
        g_beNDMWGameRam_callbackList /* callback list */
    );
}
