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
extern igMetaObject *g_beNDMWTitle2_metaObject[];
void *beBaseInfoManager_Register(void);
igMetaObject *beBaseInfoManager_GetPublishedMetaObject(void);
igMetaObject *beNDMWTitle2_GetMetaObject(void);
extern const char beNDMWTitle2_className[];
int beNDMWTitle2_GetVTable(void);
void beNDMWTitle2_InitFields(void);
extern char g_beNDMWTitle2_callbackList[];
void *beNDMWTitle2_Register(void);
}

void *beNDMWTitle2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWTitle2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWTitle2_GetMetaObject,
        beNDMWTitle2_className,
        0x34, /* instance size */
        beNDMWTitle2_GetVTable,
        beNDMWTitle2_InitFields,
        0, /* extra callback item */
        g_beNDMWTitle2_callbackList /* callback list */
    );
}
