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
extern igMetaObject *g_beNDMWStatus_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWStatus_GetMetaObject(void);
extern const char beNDMWStatus_className[];
int beNDMWStatus_GetVTable(void);
void beNDMWStatus_InitFields(void);
extern char g_beNDMWStatus_callbackList[];
void *beNDMWStatus_Register(void);
}

void *beNDMWStatus_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStatus_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWStatus_GetMetaObject,
        beNDMWStatus_className,
        0x2c, /* instance size */
        beNDMWStatus_GetVTable,
        beNDMWStatus_InitFields,
        0, /* extra callback item */
        g_beNDMWStatus_callbackList /* callback list */
    );
}
